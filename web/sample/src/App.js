import React, { Component } from "react";
import logo from "./telos.png";
import "./App.css";
import ScatterBridge  from "./scatterBridge";
import crypto from 'crypto-js';

class App extends Component {
  constructor(props) {
    super(props);

    this.state = {
      scatterBridge: null,
      network: {
        blockchain: "eos",
        protocol: "http",
        host: "127.0.0.1",
        port: 8888,
        chainId: "b7fc36d8e5891d9fea7d49df06221b3ac89c793f14e7dacd16a332ce8094d049"
      }
    };

    this.onClick = this.onClick.bind(this);
  }

  componentWillMount() {
    this.setState({
      scatterBridge: new ScatterBridge(this.state.network, "My-App")
    });
  }

  async componentDidMount() {
    await this.state.scatterBridge.connect();
    await this.state.scatterBridge.getIdentity();
  }

  makeRandStr(maxLen) {
    var str = "";
    var possible = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
  
    for (var i = 0; i < maxLen; i++) 
      str += possible.charAt(Math.floor(Math.random() * possible.length));
    
    return str;
  }
  
  async onClick(arg) {
    let actions = [];
    // let str1 = "test";
    // let str2 = "testing";
    // let hash1 = crypto.SHA256(str1);
    // let hash2 = crypto.SHA256(str2);
    let rand_str1 = this.makeRandStr(Math.floor(Math.random() * 50));
    let rand_str2 = this.makeRandStr(Math.floor(Math.random() * 50));
    let rand_str3 = crypto.SHA256(this.makeRandStr(Math.floor(Math.random() * 50)));
    let rand_str4 = crypto.SHA256(this.makeRandStr(Math.floor(Math.random() * 50)));

    // actions.push(this.state.scatterBridge.makeAction("ed1111111111", "randfromstr", {
    //   seed_user1: str1,
    //   seed_user2: str2
    // }));

    actions.push(this.state.scatterBridge.makeAction("ed1111111111", "randfromstr", {
      seed_user1: rand_str1,
      seed_user2: rand_str2
    }));

    actions.push(this.state.scatterBridge.makeAction("ed1111111111", "randfromhash", {
        hash_user1: rand_str3.toString(crypto.enc.Hex),
        hash_user2: rand_str4.toString(crypto.enc.Hex)
      }));
    
    console.log(await this.state.scatterBridge.sendTx(actions));
  }

  render() {
    return (
      <div className="App">
        <header className="App-header">
          <img src={logo} className="App-logo" alt="logo" />
          <button onClick={this.onClick}>Test</button>
        </header>
      </div>
    );
  }
}

export default App;
