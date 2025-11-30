#include <raylib.h>
#define FRAX_IMPL
#define PEBBLE_IMPL
#include "Scenes/Scenes.hpp" // Includes the above's respective libraries

static std::string DISCORD_APPLICATION_ID = "1422182414062714992";

int main() {
  Frax::Init("DanganStarFall");

  discord::RPCManager::get()
    .setClientID(DISCORD_APPLICATION_ID)
    .onReady([](discord::User const& user) {
      TraceLog(LOG_INFO, "Connected to Discord %s", user.username.c_str());
    })
    .onDisconnected([](int errcode, std::string_view message) {
      TraceLog(LOG_ERROR, "Disconnected from Discord (%d: %s)\n", errcode, message);
    })
    .onErrored([](int errcode, std::string_view message) {
      TraceLog(LOG_ERROR, "Error from Discord (%d: %s)\n", errcode, message);
    })
    .onJoinGame([](std::string_view joinSecret) {
      TraceLog(LOG_INFO, "Discord: join (%s)\n", joinSecret);
    })
    .onSpectateGame([](std::string_view spectateSecret) {
      TraceLog(LOG_INFO, "Discord: spectate (%s)\n", spectateSecret);
    })
    .onJoinRequest([](discord::User const& user) {
      TraceLog(LOG_INFO, "Request from Discord %s", user.username.c_str());
    })
    .initialize()
    .getPresence()
      .setActivityType(discord::ActivityType::Game)
      .setStatusDisplayType(discord::StatusDisplayType::Details)
      .setStartTimestamp(time(0))
      .setLargeImageKey("canary-large")
      .setLargeImageText("Dangan Starfall")
      .setSmallImageKey("chiaki")
      .setSmallImageText("Playing as Chiaki.")
      .setInstance(false);

  SceneGame().Run();

  discord::RPCManager::get().shutdown();
  Frax::Close();

  return 0;
}