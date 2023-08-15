## MacOSX issues

* The game does not compile using UE 4.27.2 on MacOS Ventura 13.4.1 due to engine source code errors. To fix this, we added additional compiler arguments to the game's `*.Target.cs` files ([file 1](blob/main/4.27/passport-features/Source/endlessrun.Target.cs) and [file 2](blob/main/4.27/passport-features/Source/endlessrunEditor.Target.cs)).

### Enable Plugin Content

![How to view plugin conent in Content Browser](Docs/how-to-view-plugin-conent.png)