#include <httpserver.h>

int main(int argc, char** argv)
{
  QCoreApplication app(argc, argv);

  // Always initialize in the main thread.
  qttp::HttpServer* httpSvr = qttp::HttpServer::getInstance();
  httpSvr->initialize();

  // Associate this call-back with the action named, "sayHello"
  auto action = httpSvr->createAction("sayHello", [](qttp::HttpData& data) {
    // Form the JSON content and let the framework handle the rest.
    QJsonObject& json = data.getResponse().getJson();
    json["hello"] = "world";
  });

  // Bind the http method, action name, and the url route together.
  httpSvr->registerRoute(action, qttp::HttpMethod::GET, "/");
  httpSvr->registerRoute(action, qttp::HttpMethod::GET, "/hello");

  // Libuv runs in its own thread.
  httpSvr->startServer();

  // Qt takes the main thread per the usual.
  return app.exec();
}
