// Generated by BUCKLESCRIPT VERSION 5.0.4, PLEASE EDIT WITH CARE
'use strict';

var Curry = require("bs-platform/lib/js/curry.js");
var React = require("react");

function getValue(e) {
  return e.target.value;
}

function Input(Props) {
  var onChange = Props.onChange;
  var name = Props.name;
  var value = Props.value;
  return React.createElement("input", {
              value: value,
              onChange: (function (e) {
                  return Curry._2(onChange, name, e.target.value);
                })
            });
}

var make = Input;

exports.getValue = getValue;
exports.make = make;
/* react Not a pure module */
