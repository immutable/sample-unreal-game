<div align="center">
  <p align="center">
    <a  href="https://docs.x.immutable.com/docs">
      <img src="https://cdn.dribbble.com/users/1299339/screenshots/7133657/media/837237d447d36581ebd59ec36d30daea.gif" width="280"/>
    </a>
  </p>
</div>

---

# sample-unreal-game

Sample Unreal Game using Unified SDK features provided by <https://github.com/immutable/unreal-immutable-sdk> plugin.

## Cloning this Repo

Before cloning this repo, ensure you have [git lfs](https://git-lfs.com/) installed.

Enable Symlinks in git repositories by running the following command:

```bash
git config --global core.symlinks true
```

This repo uses sub-modules, to clone including the correct sub-modules use the following command:
(**Note:** On Windows, you will need to use an elevated command prompt to ensure git can create the necessary symlinks)
```bash
git clone --recurse-submodules https://github.com/immutable/sample-unreal-game.git
```

To pull new changes after cloned use the following command:

```bash
git pull --recurse-submodules
```

# Running the Game

> [!WARNING]  
> This sample game is in development and login functionality does not work yet. Please use Unreal Engine 5.2 working sample if you can.

This sample game demos the passport login/logout functionality using [unreal-immmutable-sdk](https://github.com/immutable/unreal-immutable-sdk) plugin

## Quick Start

### Pre-requisites

* Unreal Engine 4.27
* Visual Studio 2019
* Jet brains Rider (Recommended)

## MacOSX issues

* The game does not compile using UE 4.27.2 on MacOS Ventura 13.4.1 due to engine source code errors. To fix this, we added additional compiler arguments to the game's `*.Target.cs` files ([file 1](blob/main/4.27/passport-features/Source/endlessrun.Target.cs) and [file 2](blob/main/4.27/passport-features/Source/endlessrunEditor.Target.cs)).

### Enable Plugin Content

![How to view plugin conent in Content Browser](Docs/how-to-view-plugin-conent.png)

## Changelog Management

The following headings should be used as appropriate.

- Added
- Changed
- Deprecated
- Removed
- Fixed

What follows is an example with all the change headings, for real world use only use headings when appropriate.
This goes at the top of the CHANGELOG.md above the most recent release.

```markdown
...

## [Unreleased]

### Added

for new features.

### Changed

for changes in existing functionality.

### Deprecated

for soon-to-be removed features.

### Removed

for now removed features.

### Fixed

for any bug fixes.

...
```

## Contributing

If you would like to contribute, please read the following:

- We use the [Conventional Commits specification](https://www.conventionalcommits.org/en/v1.0.0/#specification) when writing our commit messages. Why use Conventional Commits? Read [here](https://www.conventionalcommits.org/en/v1.0.0/#why-use-conventional-commits).

## Getting Help

Immutable X is open to all to build on, with no approvals required. If you want to talk to us to learn more, or apply for developer grants, click below:

[Contact us](https://www.immutable.com/contact)

### Project Support

To get help from other developers, discuss ideas, and stay up-to-date on what's happening, become a part of our community on Discord.

[Join us on Discord](https://discord.gg/TkVumkJ9D6)

You can also join the conversation, connect with other projects, and ask questions in our Immutable X Discourse forum.

[Visit the forum](https://forum.immutable.com/)

#### Still need help?

You can also apply for marketing support for your project. Or, if you need help with an issue related to what you're building with Immutable X, click below to submit an issue. Select _I have a question_ or _issue related to building on Immutable X_ as your issue type.

[Contact support](https://support.immutable.com/hc/en-us/requests/new)

## License
Immutable Unity SDK repository is distributed under the terms of the [Apache License (Version 2.0)](LICENSE).
