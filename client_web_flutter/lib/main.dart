import 'dart:html';

import 'package:flutter/material.dart';
import 'package:http/http.dart' as http;

void main() {
  runApp(MyApp());
}

class MyApp extends StatelessWidget {
  // This widget is the root of your application.
  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      title: 'Raspberry PI kontrolert bil',
      theme: ThemeData(
        primarySwatch: Colors.blue,
      ),
      home: MyHomePage(title: 'Raspberry PI kontrolert bil'),
    );
  }
}

class MyHomePage extends StatefulWidget {
  MyHomePage({Key key, this.title}) : super(key: key);

  // This widget is the home page of your application. It is stateful, meaning
  // that it has a State object (defined below) that contains fields that affect
  // how it looks.

  // This class is the configuration for the state. It holds the values (in this
  // case the title) provided by the parent (in this case the App widget) and
  // used by the build method of the State. Fields in a Widget subclass are
  // always marked "final".

  final String title;

  @override
  _MyHomePageState createState() => _MyHomePageState();
}

class _MyHomePageState extends State<MyHomePage> {
  @override
  Widget build(BuildContext context) {
    final _text = TextEditingController();
    bool _validate = false;

    // This method is rerun every time setState is called, for instance as done
    // by the _incrementCounter method above.
    //
    // The Flutter framework has been optimized to make rerunning build methods
    // fast, so that you can just rebuild anything that needs updating rather
    // than having to individually change instances of widgets.
    return Scaffold(
      appBar: AppBar(
        title: Text(widget.title),
      ),
      body: Center(
        // Center is a layout widget. It takes a single child and positions it
        // in the middle of the parent.
        child: Column(
          mainAxisAlignment: MainAxisAlignment.center,
          children: <Widget>[
            Text(
              'Legg inn IP adressen til serveren (raspberry pien) under:',
              style: TextStyle(fontSize: 25),
            ),
            Container(
              width: 500,
              child: TextField(
                controller: _text,
                decoration: InputDecoration(
                  hintText: "192.168.0.0:5000",
                  errorText: _validate ? 'IP invalid' : "Valid!",
                ),
              ),
            ),
            SizedBox(
              width: 50,
              height: 25,
            ),
            MaterialButton(
              onPressed: () async {
                bool verified;
                print("1");
                final response =
                    await http.get("http://" + _text.text + "/verify");
                print("2");

                print(response.body);

                if (response.statusCode == 200) {
                  verified = true;
                }

                setState(() {
                  if (verified) {
                    print("object");
                    _validate = true;
                  } else {
                    print("false");
                    _validate = false;
                  }
                });
              },
              shape: RoundedRectangleBorder(
                borderRadius: BorderRadius.circular(
                  15,
                ),
              ),
              height: 50,
              color: Colors.lightBlue,
              child: Icon(
                Icons.connect_without_contact_sharp,
                color: Colors.white,
              ), // This trailing comma makes auto-formatting nicer for build methods.
            ),
          ],
        ),
      ),
    );
  }
}
