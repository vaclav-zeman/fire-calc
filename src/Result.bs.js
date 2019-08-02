// Generated by BUCKLESCRIPT VERSION 5.0.4, PLEASE EDIT WITH CARE
'use strict';

var React = require("react");
var FormattedCurrency$ReactHooksTemplate = require("./FormattedCurrency.bs.js");

function Result(Props) {
  var targetYear = Props.targetYear;
  var targetAmount = Props.targetAmount;
  var savingsRate = Props.savingsRate;
  return React.createElement("div", {
              className: "section"
            }, React.createElement("div", {
                  className: "box"
                }, React.createElement("h2", {
                      className: "title is-3"
                    }, "Retire in: ", targetYear, " years"), React.createElement("h3", {
                      className: "title is-4"
                    }, "With savings rate: ", savingsRate), React.createElement("h3", {
                      className: "title is-4"
                    }, "Needed for retirement: ", React.createElement(FormattedCurrency$ReactHooksTemplate.make, {
                          value: targetAmount
                        }))));
}

var make = Result;

exports.make = make;
/* react Not a pure module */
