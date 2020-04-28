# dev-utils
Development tools to help crafting videogames and apps.

## Tools

### Console Log
Basic console log formatting tool. Helps printing 3 different type messages on console using standard `std::cout`.

Issue: you must a `std::endl` at final part of your output stream in order to display the message.

Usage:

`Utils::LogNotice("Gumball::Init") << "Now loading blue color." << std::endl;`

Output:

`[notice] Gumball::Init | Now loading blue color.`

Just replace `LogNotice` for any of the other two instances `LogWarning` or `LogError`.