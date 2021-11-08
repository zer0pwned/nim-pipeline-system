# Package

version       = "0.1.0"
author        = "zer0pwned"
description   = "A example nimble package to show how to use our nim build system."
license       = "MIT"
srcDir        = "src"
installExt    = @["nim"]
bin           = @["example"]


# Dependencies

requires "nim >= 1.2.0"
requires "https://github.com/status-im/nim-faststreams#99e89eb"
requires "https://github.com/status-im/nim-serialization#f9a1121"
requires "https://github.com/status-im/nim-protobuf-serialization"
