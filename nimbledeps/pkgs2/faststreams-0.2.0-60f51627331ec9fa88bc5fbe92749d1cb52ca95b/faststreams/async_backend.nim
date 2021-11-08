const
  faststreams_async_backend {.strdefine.} = "chronos"

type
  CloseBehavior* = enum
    waitAsyncClose
    dontWaitAsyncClose

const debugHelpers* = defined(debugHelpers)

when faststreams_async_backend == "chronos":
  import
    chronos

  export
    chronos

  template fsAwait*(f: Future): untyped =
    await f

elif faststreams_async_backend in ["std", "asyncdispatch"]:
  import
    std/asyncdispatch
  
  export
    asyncdispatch

  template fsAwait*(awaited: Future): untyped =
    # TODO revisit after https://github.com/nim-lang/Nim/pull/12085/ is merged
    let f = awaited
    yield f
    if not isNil(f.error):
      raise f.error
    f.read

  type Duration* = int

else:
  {.fatal: "Unrecognized network backend: " & faststreams_async_backend.}

when defined(danger):
  template fsAssert*(x) = discard
  template fsAssert*(x, msg) = discard
else:
  template fsAssert*(x) = doAssert(x)
  template fsAssert*(x, msg) = doAssert(x, msg)

template fsTranslateErrors*(errMsg: string, body: untyped) =
  try:
    body
  except IOError as err:
    raise err
  except Exception as err:
    if err[] of Defect:
      raise (ref Defect)(err)
    else:
      raise newException(IOError, errMsg, err)

template noAwait*(expr: untyped): untyped =
  expr

