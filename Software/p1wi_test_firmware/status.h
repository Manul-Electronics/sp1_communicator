class Status{
  public:
    bool wifiEnabled;
    bool wifiConnected;
    String connectedSSID;
    String dsmrMessage;

    Status(bool wifiEnabled, bool wifiConnected, String connectedSSID, String dsmrMessage){
      this->wifiEnabled = wifiEnabled;
      this->wifiConnected = wifiConnected;
      this->connectedSSID = connectedSSID;
      this->dsmrMessage = dsmrMessage;
    }

    String getStatus(){
      return String("{\"wifiEnabled\":"+String(wifiEnabled)+",\"wifiConnected\":"+String(wifiConnected)+",\"connectedSSID\":"+connectedSSID+",\"dsmrMessage\":"+dsmrMessage+"}");
    }
};
