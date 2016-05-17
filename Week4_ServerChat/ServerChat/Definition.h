#pragma once

#define CHAT_DATABASE "ChatDB.db"

#define TBL_USERS "tbl_Users"
#define USERS_USERNAME "username"
#define USERS_PASSWORD "password"
#define USERS_MAIL "mail"
#define USERS_FULLNAME "fullname"
#define USERS_ADDRESS "address"
#define USERS_SEX "sex"
#define USERS_AGE "age"
#define USERS_ISONLINE "isOnline"

#define TBL_FRIENDS "tbl_Friends"
#define FRIENDS_USER "user"
#define FRIENDS_FR "friend"

#define TBL_MESSAGES "tbl_Messages"
#define MESSAGES_ID "messID"
#define MESSAGES_SENDER "messSender"
#define MESSAGES_RECEIVER "messReceiver"
#define MESSAGES_CONTENT "messContent"
#define MESSAGES_WAS_READ "wasRead"

#define JSON_LOGIN 1
#define JSON_LOGOUT 2
#define JSON_REGIST 3
#define JSON_RECV_MESSAGE 4
#define JSON_SEND_MESSAGE 5
#define JSON_LIST_MESSAGE 6
#define JSON_ADD_FRIEND	7
#define JSON_DEL_FRIEND 8
#define JSON_LIST_FRIEND 9

#define ANONYMOUS "anonymous"
#define DEFAULT_PORT 12345
#define BUFFER_LENGTH 1024
#define FORCE_LOGOUT "{\"type\":2,\"Logout\":{\"username\":\"\"}}"