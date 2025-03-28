<!-- markdownlint-disable MD041 -->
<!-- markdownlint-disable MD033 -->
<div align="center">
  <p align="center">
    <a  href="https://docs.x.immutable.com/docs">
      <img src="https://cdn.dribbble.com/users/1299339/screenshots/7133657/media/837237d447d36581ebd59ec36d30daea.gif" width="280" alt="Immutable Animation"/>
    </a>
  </p>
</div>
<!-- markdownlint-enable MD033 -->

---

# Unreal Engine Sample Game

This Unreal Engine sample game demos features provided by the <https://github.com/immutable/unreal-immutable-sdk> plugin. It is built with Unreal Engine 4.26 (the min Unreal Engine version the Unreal SDK supports), so the sample blueprints are compatible with newer versions of Unreal Engine.

## Cloning this Repo

> Before cloning this repo, ensure you have [git lfs](https://git-lfs.com/) installed.

This repo uses sub-modules, to clone including the correct sub-modules use the following command:

```bash
git clone --recurse-submodules git@github.com:immutable/sample-unreal-game.git
```

To pull new changes after cloned use the following command:

```bash
git pull --recurse-submodules
```

The submodules include the [BLUI](https://github.com/immutable/immutable-BLUI) and [unreal-immutable-sdk](https://github.com/immutable/unreal-immutable-sdk) repositories, which get cloned into the `Plugins` directory with the correct plugin settings configured for BLUI and the Unreal SDK to work out of the box without additional setup steps.

### Backend Submodule

The `Backend` folder is a submodule linked to the `feat/list-asset` branch of the [unity-sdk-game-tutorial](https://github.com/immutable/unity-sdk-game-tutorial/tree/feat/list-asset) repo so the Unreal sample game can re-use the `contracts`, `json-server`, and `mint-backend` modules from the tutorial repo. The tutorial repo includes a lot of Unity specific assets and files which are not used in the Unreal game game but they can be ignored by configuring sparse checkout with git.

To configure sparse checkout and only clone the `contracts`, `json-server`, and `mint-backend` modules into the `Backend` folder:

1. Create a `sparse-checkout` file in the `.git/modules/Backend/info` folder:

    ```shell
    # open a terminal at the root of the sample game repo
    touch .git/modules/Backend/info/sparse-checkout
    ```

2. Add the folder paths from the tutorial repo you wish to clone:

    ```shell
    echo "contracts/*" >> .git/modules/Backend/info/sparse-checkout
    echo "json-server/*" >> .git/modules/Backend/info/sparse-checkout
    echo "mint-backend/*" >> .git/modules/Backend/info/sparse-checkout
    ```

3. Checkout the branch:

    ```shell
    cd Backend/
    git checkout feat/list-asset
    ```

Now there should only be the `contracts`, `json-server`, and `mint-backend` folders in the sample game `Backend` folder.

> Note: the sparse checkout config is local only and won't get pushed to remote, so this will need to be setup **once** the first time the repo is cloned.

See the `README` files in the `contracts`, `json-server`, and `mint-backend` folders for how to use the backend servers for local development or to deploy contracts.

# Running the Game

## Pre-requisites

* Unreal Engine 4.26 (or newer)
* Visual Studio 2019

## Quick Start

After cloning the repo, double click the `SampleGame426` uproject file in the file explorer will build the project and launch Unreal Engine 4.26.

## Enable Plugin Content

![How to view plugin content in Content Browser](Docs/how-to-view-plugin-conent.png)

* Open the `Content Browser`
* Click on `View Options` button in the bottom right corner of the `Content Browser` window
* Select `Show Plugin Content`

The `Immutable Content` folder includes sample blueprints from the `unreal-immutable-sdk` plugin.

## BLUI

For Unreal Engine 4.26 and 4.27, the Unreal SDK use BLUI plugin instead of `WebBrowserWidget` plugin. Normally when installing the Unreal SDK into a project there are additional requirements for setting up BLUI. This project comes with the `WebBroswerWidget` and BLUI setup correctly and should work without any additional configuration.

More information about BLUI can be found on the [Unreal SDK installation](https://docs.immutable.com/sdks/zkEVM/unreal#installation) docs.

## Changelog Management

The following headings should be used as appropriate.

* Added
* Changed
* Deprecated
* Removed
* Fixed

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

* We use the [Conventional Commits specification](https://www.conventionalcommits.org/en/v1.0.0/#specification) when writing our commit messages. Why use Conventional Commits? Read [here](https://www.conventionalcommits.org/en/v1.0.0/#why-use-conventional-commits).

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
