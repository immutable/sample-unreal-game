# passport-features

This sample game demos the passport login/logout functionality using [unreal-immmutable-sdk](https://github.com/immutable/unreal-immutable-sdk) plugin

## Quick Start

### Pre-requisites

* Unreal Engine 5.2
* Visual Studio 2022
* Jet brains Rider (Recommended)

### Run game

* Open the project file `endlessrun.uproject`
* Build project using Jetbrains Rider or Visual Studio IDE
* Open MainMenu at `5.2/passport-features/Content/ThirdPersonBP/UI/MainMenu/MainMenu.uasset`
* Press play button to run the game

### Game Play Functionality

* The game is to avoid blocking trees and collect coins. Once 10 or more coins are collected, the game will prompt to login with Passport to continue playing.
* Press `Continue with Passport` button to login, it will then launch a browser to authenticate with Passport login flow. Once authenticated, the game will continue.

### Test passport login functionality provided by [unreal-immmutable-sdk](https://github.com/immutable/unreal-immutable-sdk) plugin

* Navigate to Content Browser -> Plugins -> Blueprints -> PassportBlueprintSample
* Play game (should launch browser for authentication)
