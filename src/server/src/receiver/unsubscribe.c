/*
** EPITECH PROJECT, 2023
** B-NWP-400-PAR-4-1-myteams-jeras.bertine
** File description:
** unsubscribe
*/

#include "server.h"

int check_user_sub(server_t *server, char *user_uuid, char *team_uuid,
int index);

static int remove_member_team(teams_t *team, uuid_t user_uuid)
{
    for (int i = 0; i < team->subs_nbr; i++) {
        if (uuid_compare(team->members_uuid[i], user_uuid) == 0) {
            team->subs_nbr--;
            memmove(&team->members_uuid[i], &team->members_uuid[i + 1],
            (team->subs_nbr - i) * sizeof(uuid_t));
            return 0;
        }
    }
    return 1;
}

static int leave_teams(user_t *user, uuid_t team_uuid)
{
    for (int i = 0; i < user->nbr_teams; i++) {
        if (uuid_compare(user->teams_uuid[i], team_uuid) == 0) {
            user->nbr_teams--;
            memmove(&user->teams_uuid, &user->teams_uuid[i + 1],
            (user->nbr_teams - i) * sizeof(uuid_t));
            return 0;
        }
    }
    return 1;
}

static int send_response(server_t *server, int client_fd,
client_packet recv_data)
{
    server_packet data;
    char team_str[MAX_UUID_LENGTH];
    char user_str[MAX_UUID_LENGTH];

    uuid_unparse(recv_data.team_uuid, team_str);
    uuid_unparse(recv_data.user_uuid, user_str);
    server_event_user_unsubscribed(team_str, user_str);
    data.type = TYPE_UNSUBSCRIBE;
    uuid_copy(data.team_uuid, recv_data.team_uuid);
    uuid_copy(data.user_uuid, recv_data.user_uuid);
    data.code = CODE_200;
    send(client_fd, &data, sizeof(data), 0);
    return 0;
}

int receive_unsubscribe(server_t *server, int index, client_packet recv_data)
{
    teams_t *team = index_of_team(&server->data, recv_data);
    user_t *user = index_of_user(&server->data, recv_data.user_uuid);

    if (team == NULL || user == NULL)
        return 1;

    for (int i = 0; i < team->subs_nbr; i++) {
        if (uuid_compare(team->members_uuid[i], recv_data.user_uuid) == 0) {
            remove_member_team(team, recv_data.user_uuid);
            leave_teams(user, recv_data.team_uuid);
            send_response(server, server->addrs.clients[index].fd, recv_data);
        }
    }
    return 0;
}
