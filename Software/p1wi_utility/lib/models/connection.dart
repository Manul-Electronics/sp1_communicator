class Connection{
  final String port;
  final int baudrate;
  final int parity;
  final int stopbit;

  bool opened = false;

  Connection(this.port, this.baudrate, this.parity, this.stopbit);
}