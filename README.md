<h1 align=center>Yaru window decoration</h1>

An experimental Flutter plugin to create modern looking window decorations (rounded corners, light window border) on Linux, without libhandy.

## Usage

Add the package to your pubspec:

```
dependencies:
  yaru_window_decoration:
    git:
      url: https://github.com/Jupi007/yaru_window_decoration.dart
```

This package comes with a plugin that loads a custom stylesheet which patch the window decoration shadow and background.

Then, wrap your app with the `YaruWindowDecoration` widget:

```dart
class MyApp extends StatelessWidget {
  @override
  Widget build(BuildContext context) {
    return YaruWindowDecoration(
      child: // ...
    );
  }
}
```

This widget provides the rounded corners and the window border.
It must be placed in the widget tree as soon as possible.
