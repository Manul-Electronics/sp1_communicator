import 'dart:typed_data';
import 'package:flutter_libserialport/flutter_libserialport.dart';
import 'package:p1wi_utility/models/models.dart';

class SerialController{

  SerialPort? serial;
  SerialPortReader? reader;

  SerialController();

  bool open(Connection connection){
    try{
      serial = SerialPort(connection.port);
      if(serial != null){
        serial!.config = SerialPortConfig()
          ..baudRate=connection.baudrate
          ..parity=connection.parity
          ..stopBits=connection.stopbit;

        serial!.open(mode: SerialPortMode.readWrite);

        reader = SerialPortReader(serial!);

        if(reader != null){
          reader!.stream.listen(
            (data){ 
            }
          );
        }

        return serial!.isOpen;
      }
      else{
        return false;
      }
    }
    on SerialPortError catch(ex){
      print("SerialPortError : $ex");
      return false;
    }
  }

  bool close(){
    if(serial != null){
      try{
        return serial!.close();
      }
      on SerialPortError catch(ex){
        print("SerialPortError : $ex");
        return false;
      }
    }
    else{
      return false;
    }
  }

  void write(String payload){
    if(serial != null && serial!.isOpen){
      try{
        serial!.write(Uint8List.fromList(payload.codeUnits));
      }
      on SerialPortError catch (ex){
        print("SerialPortError : $ex");
      }
    }
  }

  String convert(Uint8List raw){
    String message = String.fromCharCodes(raw);

    return message;
  }

  String? read(){
    if(serial != null && serial!.isOpen){
      try{
        if(serial!.bytesAvailable > 0){
          return String.fromCharCodes(serial!.read(serial!.bytesAvailable));
        }
        else{
          return null;
        }
      }
      on SerialPortError catch(ex){
        print("SerialPortError : $ex");
        return null;
      }
    }
    else{
      return null;
    }
  }

  String? readUntil(String delimiter){
    if(serial != null && serial!.isOpen){
      try{
        if(serial!.bytesAvailable > 0){
          String rawString = String.fromCharCodes(serial!.read(serial!.bytesAvailable));

          return rawString.substring(0, rawString.indexOf(delimiter));
        }
        else{
          return null;
        }
      }
      on SerialPortError catch(ex){
        print("SerialPortError : $ex");
        return null;
      }
    }
    else{
      return null;
    }
  }
}