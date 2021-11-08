import protobuf_serialization
import_proto3 "protocol.proto3"

proc protoExample*(): string = 
  let x = ExampleMsg(a: 10, b: "welcome to something you dont understand.")
  let encoded = Protobuf.encode(x)
  let decoded = Protobuf.decode(encoded, ExampleMsg)
  decoded.b
