(window.webpackJsonp=window.webpackJsonp||[]).push([[9],{175:function(t,n,a){"use strict";a.r(n);var s=a(0),e=Object(s.a)({},function(){var t=this,n=t.$createElement,a=t._self._c||n;return a("div",{staticClass:"content"},[t._m(0),t._v(" "),t._m(1),t._v(" "),t._m(2),t._v(" "),t._m(3),t._v(" "),t._m(4),t._v(" "),a("p",[t._v("Want another example? Toggle. If you need to toggle the current state of a digital\noutput, you need an helper variable to keep track of the state (and remember to "),a("strong",[t._v("ALWAYS")]),t._v("\nupdate that variable when you write to the output). With a class, the state is\ntightly bound to the instance, so you have a "),a("a",{attrs:{href:"https://en.wikipedia.org/wiki/Single_source_of_truth",target:"_blank",rel:"noopener noreferrer"}},[t._v("single source of truth"),a("OutboundLink")],1),t._v(":\n"),a("code",[t._v("turnOn()")]),t._v(", "),a("code",[t._v("turnOff()")]),t._v(" and "),a("code",[t._v("toggle()")]),t._v(" will take care of updating the inner state accordingly.")]),t._v(" "),t._m(5),t._m(6),t._v(" "),t._m(7),t._m(8)])},[function(){var t=this.$createElement,n=this._self._c||t;return n("h1",{attrs:{id:"io-pin"}},[n("a",{staticClass:"header-anchor",attrs:{href:"#io-pin","aria-hidden":"true"}},[this._v("#")]),this._v(" io::Pin")])},function(){var t=this.$createElement,n=this._self._c||t;return n("p",[n("code",[this._v("Pin")]),this._v(" is an abstract class for pin manipulation. You won't use it directly,\nbut through its specialized implementations:")])},function(){var t=this.$createElement,n=this._self._c||t;return n("ol",[n("li",[this._v("DigitalIn")]),this._v(" "),n("li",[this._v("DigitalOut")]),this._v(" "),n("li",[this._v("AnalogIn")]),this._v(" "),n("li",[this._v("AnalogOut")])])},function(){var t=this.$createElement,n=this._self._c||t;return n("p",[this._v("These classes will let you stop writing horrible code like "),n("code",[this._v("digitalWrite(led, HIGH)")]),this._v("\nand do "),n("code",[this._v("led.turnOn()")]),this._v(" instead, for example.")])},function(){var t=this,n=t.$createElement,a=t._self._c||n;return a("p",[t._v("You may be asking if a whole class to save a few keystrokes is whortwhile. I strongly\nbelieve it is!\nWhat's the use case, you may ask? Well, one emblematic example is that of the\nbuiltin led on the ESP8266: it is active low, so you write "),a("code",[t._v("digitalWrite(BUILTIN_LED, LOW)")]),t._v("\nto actually turn it on. Does it look intuitive? Does it look "),a("em",[t._v("eloquent")]),t._v("? Not really.\n"),a("code",[t._v("builtinLed.turnOn()")]),t._v(" does, however. All you need to get it working is calling\n"),a("code",[t._v("builtinLed.activeLow()")]),t._v(" in your setup to hide the reversed logic.")])},function(){var t=this,n=t.$createElement,a=t._self._c||n;return a("div",{staticClass:"language-c extra-class"},[a("pre",{pre:!0,attrs:{class:"language-c"}},[a("code",[a("span",{pre:!0,attrs:{class:"token comment"}},[t._v("// BEFORE")]),t._v("\n"),a("span",{pre:!0,attrs:{class:"token macro property"}},[t._v("#"),a("span",{pre:!0,attrs:{class:"token directive keyword"}},[t._v("define")]),t._v(" LED 1")]),t._v("\n\nbool ledState "),a("span",{pre:!0,attrs:{class:"token operator"}},[t._v("=")]),t._v(" true"),a("span",{pre:!0,attrs:{class:"token punctuation"}},[t._v(";")]),t._v("\n\n"),a("span",{pre:!0,attrs:{class:"token function"}},[t._v("loop")]),a("span",{pre:!0,attrs:{class:"token punctuation"}},[t._v("(")]),a("span",{pre:!0,attrs:{class:"token punctuation"}},[t._v(")")]),t._v(" "),a("span",{pre:!0,attrs:{class:"token punctuation"}},[t._v("{")]),t._v("\n    "),a("span",{pre:!0,attrs:{class:"token function"}},[t._v("digitalWrite")]),a("span",{pre:!0,attrs:{class:"token punctuation"}},[t._v("(")]),t._v("LED"),a("span",{pre:!0,attrs:{class:"token punctuation"}},[t._v(",")]),t._v(" ledState"),a("span",{pre:!0,attrs:{class:"token punctuation"}},[t._v(")")]),a("span",{pre:!0,attrs:{class:"token punctuation"}},[t._v(";")]),t._v("\n    ledState "),a("span",{pre:!0,attrs:{class:"token operator"}},[t._v("=")]),t._v(" "),a("span",{pre:!0,attrs:{class:"token operator"}},[t._v("!")]),t._v("ledState\n"),a("span",{pre:!0,attrs:{class:"token punctuation"}},[t._v("}")]),t._v("\n\n\n"),a("span",{pre:!0,attrs:{class:"token comment"}},[t._v("// AFTER")]),t._v("\nDigitalOut "),a("span",{pre:!0,attrs:{class:"token function"}},[t._v("led")]),a("span",{pre:!0,attrs:{class:"token punctuation"}},[t._v("(")]),a("span",{pre:!0,attrs:{class:"token number"}},[t._v("1")]),a("span",{pre:!0,attrs:{class:"token punctuation"}},[t._v(")")]),a("span",{pre:!0,attrs:{class:"token punctuation"}},[t._v(";")]),t._v("\n\n"),a("span",{pre:!0,attrs:{class:"token keyword"}},[t._v("void")]),t._v(" "),a("span",{pre:!0,attrs:{class:"token function"}},[t._v("loop")]),a("span",{pre:!0,attrs:{class:"token punctuation"}},[t._v("(")]),a("span",{pre:!0,attrs:{class:"token punctuation"}},[t._v(")")]),t._v(" "),a("span",{pre:!0,attrs:{class:"token punctuation"}},[t._v("{")]),t._v("\n    led"),a("span",{pre:!0,attrs:{class:"token punctuation"}},[t._v(".")]),a("span",{pre:!0,attrs:{class:"token function"}},[t._v("toggle")]),a("span",{pre:!0,attrs:{class:"token punctuation"}},[t._v("(")]),a("span",{pre:!0,attrs:{class:"token punctuation"}},[t._v(")")]),a("span",{pre:!0,attrs:{class:"token punctuation"}},[t._v(";")]),t._v("\n"),a("span",{pre:!0,attrs:{class:"token punctuation"}},[t._v("}")]),t._v("\n")])])])},function(){var t=this.$createElement,n=this._self._c||t;return n("p",[this._v("Not convinced yet? What if you have an analog input and want to know if its valued\nchanged by at least X from your latest reading? You would need an helper variable\nagain. Now imagine if you have 5 analog inputs you want to track: you'll end up\nwith 10 variables and of course you have again to "),n("em",[this._v("ALWAYS")]),this._v(" keep both in sync.\n"),n("code",[this._v("AnalogIn")]),this._v(", conveniently, provides a "),n("code",[this._v("delta()")]),this._v(" method that gives you the change\nfrom the previous reading and will always be in sync. Awesome!")])},function(){var t=this,n=t.$createElement,a=t._self._c||n;return a("div",{staticClass:"language-c extra-class"},[a("pre",{pre:!0,attrs:{class:"language-c"}},[a("code",[a("span",{pre:!0,attrs:{class:"token comment"}},[t._v("// BEFORE")]),t._v("\n"),a("span",{pre:!0,attrs:{class:"token macro property"}},[t._v("#"),a("span",{pre:!0,attrs:{class:"token directive keyword"}},[t._v("define")]),t._v(" INPUT1 A1")]),t._v("\n"),a("span",{pre:!0,attrs:{class:"token macro property"}},[t._v("#"),a("span",{pre:!0,attrs:{class:"token directive keyword"}},[t._v("define")]),t._v(" INPUT2 A2")]),t._v("\n\nuint16_t current1"),a("span",{pre:!0,attrs:{class:"token punctuation"}},[t._v(",")]),t._v(" prev1"),a("span",{pre:!0,attrs:{class:"token punctuation"}},[t._v(";")]),t._v("\nuint16_t current2"),a("span",{pre:!0,attrs:{class:"token punctuation"}},[t._v(",")]),t._v(" prev2"),a("span",{pre:!0,attrs:{class:"token punctuation"}},[t._v(";")]),t._v("\n\n"),a("span",{pre:!0,attrs:{class:"token keyword"}},[t._v("void")]),t._v(" "),a("span",{pre:!0,attrs:{class:"token function"}},[t._v("loop")]),a("span",{pre:!0,attrs:{class:"token punctuation"}},[t._v("(")]),a("span",{pre:!0,attrs:{class:"token punctuation"}},[t._v(")")]),t._v(" "),a("span",{pre:!0,attrs:{class:"token punctuation"}},[t._v("{")]),t._v("\n    prev1 "),a("span",{pre:!0,attrs:{class:"token operator"}},[t._v("=")]),t._v(" current1"),a("span",{pre:!0,attrs:{class:"token punctuation"}},[t._v(";")]),t._v("\n    current1 "),a("span",{pre:!0,attrs:{class:"token operator"}},[t._v("=")]),t._v(" "),a("span",{pre:!0,attrs:{class:"token function"}},[t._v("analogRead")]),a("span",{pre:!0,attrs:{class:"token punctuation"}},[t._v("(")]),t._v("INPUT1"),a("span",{pre:!0,attrs:{class:"token punctuation"}},[t._v(")")]),a("span",{pre:!0,attrs:{class:"token punctuation"}},[t._v(";")]),t._v("\n    prev2 "),a("span",{pre:!0,attrs:{class:"token operator"}},[t._v("=")]),t._v(" current2"),a("span",{pre:!0,attrs:{class:"token punctuation"}},[t._v(";")]),t._v("\n    current2 "),a("span",{pre:!0,attrs:{class:"token operator"}},[t._v("=")]),t._v(" "),a("span",{pre:!0,attrs:{class:"token function"}},[t._v("analogRead")]),a("span",{pre:!0,attrs:{class:"token punctuation"}},[t._v("(")]),t._v("INPUT2"),a("span",{pre:!0,attrs:{class:"token punctuation"}},[t._v(")")]),a("span",{pre:!0,attrs:{class:"token punctuation"}},[t._v(";")]),t._v("\n\n    "),a("span",{pre:!0,attrs:{class:"token keyword"}},[t._v("if")]),t._v(" "),a("span",{pre:!0,attrs:{class:"token punctuation"}},[t._v("(")]),a("span",{pre:!0,attrs:{class:"token function"}},[t._v("abs")]),a("span",{pre:!0,attrs:{class:"token punctuation"}},[t._v("(")]),t._v("current1 "),a("span",{pre:!0,attrs:{class:"token operator"}},[t._v("-")]),t._v(" prev1"),a("span",{pre:!0,attrs:{class:"token punctuation"}},[t._v(")")]),t._v(" "),a("span",{pre:!0,attrs:{class:"token operator"}},[t._v(">")]),t._v(" THRESHOLD"),a("span",{pre:!0,attrs:{class:"token punctuation"}},[t._v(")")]),t._v("\n        "),a("span",{pre:!0,attrs:{class:"token punctuation"}},[t._v(".")]),a("span",{pre:!0,attrs:{class:"token punctuation"}},[t._v(".")]),a("span",{pre:!0,attrs:{class:"token punctuation"}},[t._v(".")]),t._v("\n\n\n"),a("span",{pre:!0,attrs:{class:"token comment"}},[t._v("// AFTER")]),t._v("\nAnalogIn "),a("span",{pre:!0,attrs:{class:"token function"}},[t._v("input1")]),a("span",{pre:!0,attrs:{class:"token punctuation"}},[t._v("(")]),t._v("A1"),a("span",{pre:!0,attrs:{class:"token punctuation"}},[t._v(")")]),a("span",{pre:!0,attrs:{class:"token punctuation"}},[t._v(",")]),t._v(" "),a("span",{pre:!0,attrs:{class:"token function"}},[t._v("input2")]),a("span",{pre:!0,attrs:{class:"token punctuation"}},[t._v("(")]),t._v("A2"),a("span",{pre:!0,attrs:{class:"token punctuation"}},[t._v(")")]),a("span",{pre:!0,attrs:{class:"token punctuation"}},[t._v(";")]),t._v("\n\n"),a("span",{pre:!0,attrs:{class:"token keyword"}},[t._v("void")]),t._v(" "),a("span",{pre:!0,attrs:{class:"token function"}},[t._v("loop")]),a("span",{pre:!0,attrs:{class:"token punctuation"}},[t._v("(")]),a("span",{pre:!0,attrs:{class:"token punctuation"}},[t._v(")")]),t._v(" "),a("span",{pre:!0,attrs:{class:"token punctuation"}},[t._v("{")]),t._v("\n    input1"),a("span",{pre:!0,attrs:{class:"token punctuation"}},[t._v(".")]),a("span",{pre:!0,attrs:{class:"token function"}},[t._v("read")]),a("span",{pre:!0,attrs:{class:"token punctuation"}},[t._v("(")]),a("span",{pre:!0,attrs:{class:"token punctuation"}},[t._v(")")]),a("span",{pre:!0,attrs:{class:"token punctuation"}},[t._v(";")]),t._v("\n    input2"),a("span",{pre:!0,attrs:{class:"token punctuation"}},[t._v(".")]),a("span",{pre:!0,attrs:{class:"token function"}},[t._v("read")]),a("span",{pre:!0,attrs:{class:"token punctuation"}},[t._v("(")]),a("span",{pre:!0,attrs:{class:"token punctuation"}},[t._v(")")]),a("span",{pre:!0,attrs:{class:"token punctuation"}},[t._v(";")]),t._v("\n\n    "),a("span",{pre:!0,attrs:{class:"token keyword"}},[t._v("if")]),t._v(" "),a("span",{pre:!0,attrs:{class:"token punctuation"}},[t._v("(")]),t._v("input1"),a("span",{pre:!0,attrs:{class:"token punctuation"}},[t._v(".")]),a("span",{pre:!0,attrs:{class:"token function"}},[t._v("absDelta")]),a("span",{pre:!0,attrs:{class:"token punctuation"}},[t._v("(")]),a("span",{pre:!0,attrs:{class:"token punctuation"}},[t._v(")")]),t._v(" "),a("span",{pre:!0,attrs:{class:"token operator"}},[t._v(">")]),t._v(" THRESHOLD"),a("span",{pre:!0,attrs:{class:"token punctuation"}},[t._v(")")]),t._v("\n        "),a("span",{pre:!0,attrs:{class:"token punctuation"}},[t._v(".")]),a("span",{pre:!0,attrs:{class:"token punctuation"}},[t._v(".")]),a("span",{pre:!0,attrs:{class:"token punctuation"}},[t._v(".")]),t._v("\n"),a("span",{pre:!0,attrs:{class:"token punctuation"}},[t._v("}")]),t._v("\n")])])])},function(){var t=this.$createElement,n=this._self._c||t;return n("p",[this._v("Does it feel more "),n("em",[this._v("natural")]),this._v("?")])}],!1,null,null,null);n.default=e.exports}}]);