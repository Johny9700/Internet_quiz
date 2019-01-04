# Internet_quiz

## Build info:

### Client:
  use "make" in "client/build-client_app-Desktop-Debug" directory
  
### Server:
  use "make" in server directory
  
## TODO
- Top 3 ranking (now server sends hardcoded, always the same ranking)
- Solve problem with merging messages
- Clean fields after questions and disconnecting from game
  
## Possible bugs
  
- When server detects problem with connection with client outside client thread loop (ex. when broadcasting some message) it will remove client data from vector but client thread will be still running -- patch cooming soon ;)
