// Generated by BUCKLESCRIPT VERSION 5.0.4, PLEASE EDIT WITH CARE
'use strict';

var Curry = require("bs-platform/lib/js/curry.js");
var React = require("react");

function getValue(e) {
  return e.target.value;
}

function Input(Props, name, onChange, value) {
  return React.createElement("input", {
              name: name,
              value: value,
              onChange: Curry._2(onChange, name, getValue)
            });
}

var make = Input;

exports.getValue = getValue;
exports.make = make;
/* react Not a pure module */
