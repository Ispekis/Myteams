/*
** EPITECH PROJECT, 2023
** B-NWP-400-PAR-4-1-myteams-jeras.bertine
** File description:
** subscribe
*/

#include "server.h"

int member_add_team(user_t *user, uuid_t team_uuid)
{
    uuid_t *new = realloc(user->teams_uuid,
    sizeof(uuid_t) * (user->nbr_teams + 1));

    user->teams_uuid = new;
    uuid_copy(user->teams_uuid[user->nbr_teams], team_uuid);
    user->nbr_teams++;
    return 0;
}

int join_teams(teams_t *team, uuid_t user_uuid)
{
    uuid_t *new = realloc(team->members_uuid,
    sizeof(uuid_t) * (team->subs_nbr + 1));

    team->members_uuid = new;
    uuid_copy(team->members_uuid[team->subs_nbr], user_uuid);
    team->subs_nbr++;
    return 0;
}

static int send_response(int client_fd, uuid_t team_uuid, uuid_t user_uuid)
{
    server_packet data;
    char team_str[MAX_UUID_LENGTH];
    char user_str[MAX_UUID_LENGTH];

    uuid_unparse(team_uuid, team_str);
    uuid_unparse(user_uuid, user_str);
    server_event_user_subscribed(team_str, user_str);
    data.type = TYPE_SUBSCRIBE;
    uuid_copy(data.team_uuid, team_uuid);
    uuid_copy(data.user_uuid, user_uuid);
    data.code = CODE_200;
    send(client_fd, &data, sizeof(data), 0);
    return 0;
}

int is_subscribed(user_t *user, uuid_t team_uuid, int client_fd)
{
    for (int i = 0; i < user->nbr_teams; i++) {
        if (uuid_compare(user->teams_uuid[i], team_uuid) == 0) {
            return -1;
        }
    }
    return 0;
}

int receive_subscribe(server_t *server, int index, client_packet recv_data)
{
    teams_t *team = index_of_team(&server->data, recv_data);
    user_t *user = index_of_user(&server->data, recv_data.user_uuid);

    if (team == NULL || user == NULL)
        return 1;

    if (is_subscribed(user, recv_data.team_uuid,
    server->addrs.clients[index].fd) == -1)
        return 1;
    join_teams(team, recv_data.user_uuid);
    member_add_team(user, recv_data.team_uuid);
    send_response(server->addrs.clients[index].fd, recv_data.team_uuid,
    recv_data.user_uuid);
    return 0;
}
