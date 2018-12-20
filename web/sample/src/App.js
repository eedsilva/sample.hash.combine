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
        chainId: "5c414e20cb772e0d634a3a1e54587bc49ea5b3a11c1991dc4548f93d72f9621f"
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

  makeRandStr(max) {
    var text = "";
    var possible = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
  
    for (var i = 0; i < max; i++) 
      text += possible.charAt(Math.floor(Math.random() * possible.length));
    
    return text;
  }
  
  async onClick(arg) {
    let actions = [];
    let str1 = "test";
    let str2 = "testing";
    let hash1 = crypto.SHA256(str1);
    let hash2 = crypto.SHA256(str2);
    
    actions.push(this.state.scatterBridge.makeAction("ed1111111111", "randfromstr", {
      seed_user1: str1,
      seed_user2: str2
    }));

    actions.push(this.state.scatterBridge.makeAction("ed1111111111", "randfromstr", {
      seed_user1: this.makeRandStr(Math.floor(Math.random() * 30)),
      seed_user2: this.makeRandStr(Math.floor(Math.random() * 30))
    }));
    
    actions.push(this.state.scatterBridge.makeAction("ed1111111111", "randfromhash", {
        hash_user1: hash1.toString(crypto.enc.Hex),
        hash_user2: hash2.toString(crypto.enc.Hex)
      }));
    
    await this.state.scatterBridge.sendTx(actions);
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
