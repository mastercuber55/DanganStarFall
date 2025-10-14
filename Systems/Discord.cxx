#include "index.hpp"
#include <string>
#ifndef PLATFORM_ANDROID
#include "discord_rpc.h"
#include <raylib.h>

void handlerReady(const DiscordUser *user) {
  TraceLog(LOG_INFO, "Connected to Discord %s", user->username);
}

void handleDisconnection(int errcode, const char *message) {
  TraceLog(LOG_INFO, "Disconnected from Discord (%d: %s)\n", errcode, message);
}

void handleError(int errcode, const char *message) {
  TraceLog(LOG_ERROR, "Error from Discord (%d: %s)\n", errcode, message);
}

void handleJoin(const char *secret) {
  TraceLog(LOG_INFO, "Discord: join (%s)\n", secret);
}

void handleSpectate(const char *secret) {
  printf("\nDiscord: spectate (%s)\n", secret);
}

void handleJoinRequest(const DiscordUser *request) {
  TraceLog(LOG_INFO, "Request from Discord %s", request->username);

  Discord_Respond(request->userId, DISCORD_REPLY_YES);
}

static DiscordRichPresence rpc = {};

static std::string APPLICATION_ID = "1422182414062714992";

void Discord::Init() {

  DiscordEventHandlers handlers{};
  handlers.ready = handlerReady;
  handlers.disconnected = handleDisconnection;
  handlers.errored = handleError;
  handlers.joinGame = handleJoin;
  handlers.joinRequest = handleJoinRequest;
  handlers.spectateGame = handleSpectate;

  Discord_Initialize(APPLICATION_ID.c_str(), &handlers, 1, nullptr);

  rpc.instance = 1;
  rpc.startTimestamp = time(0);
  rpc.largeImageKey = "canary-large";
  rpc.largeImageText = "Dangan Starfall";
  rpc.smallImageKey = "chiaki";
  rpc.smallImageText = "Playing as Chiaki.";
  // rpc.partyId = "76324";
  // rpc.partySize = 1;
  // rpc.partyMax = 100;
  // rpc.matchSecret = "zxcvb";
  // rpc.joinSecret = "dfghjk";
  // rpc.spectateSecret = "tyul";
}

void Discord::Update(const std::string &details, const std::string &state) {

  rpc.details = details.c_str();
  rpc.state = state.c_str();

  Discord_UpdatePresence(&rpc);
}

void Discord::Close() { Discord_Shutdown(); }

void Discord::Callbacks() { Discord_RunCallbacks(); }
#else
void Discord::Init() {}

void Discord::Update(const std::string &details, const std::string &state) {}

void Discord::Close() {}

void Discord::Callbacks() {}
#endif