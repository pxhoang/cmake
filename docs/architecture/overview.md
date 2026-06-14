# Architecture Overview

The project uses Clean Architecture inside each binary.

Flow:

```text
main.cpp -> bootstrap -> api -> application -> domain/persistence
```

The API is an in-process C++ function-call API, not HTTP/TCP.
