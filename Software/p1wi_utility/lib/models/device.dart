class Device{
  bool isConnected = false;
  String uid;
  String port;
  String vid = "";
  String pid = "";

  Device(this.uid, this.port);
}