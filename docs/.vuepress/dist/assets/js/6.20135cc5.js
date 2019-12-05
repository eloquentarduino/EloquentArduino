(window.webpackJsonp=window.webpackJsonp||[]).push([[6],{172:function(t,n,a){"use strict";a.r(n);var s=a(0),e=Object(s.a)({},function(){var t=this,n=t.$createElement,a=t._self._c||n;return a("div",{staticClass:"content"},[t._m(0),t._v(" "),t._m(1),t._v(" "),a("p",[t._v('Why do we need input streams? Because we can manipulate them using\na uniform interface. We can carry all sort of operations on the values\ngenerated by the stream, careless of where those values come from.\nThis means we can implement "abstract" algorithms that can be reused\nmultiple times on different data.')]),t._v(" "),a("p",[t._v("Want an example? Let's say you want to apply "),a("a",{attrs:{href:"https://en.wikipedia.org/wiki/Exponential_smoothing",target:"_blank",rel:"noopener noreferrer"}},[t._v("Exponential Smoothing"),a("OutboundLink")],1),t._v("\nto an analog potentiometer. To get this working you will need 3 variables: the current value, the past value\nand the smoothing factor (in the range ]0, 1]). "),a("br"),t._v("\nWith the InputStream construct you may use a "),a("code",[t._v("Transformer")]),t._v(" instead.\nA Transformer is a class that gets values from an input stream and transforms\nthem in some way. So an exponential smoothing transformer in action over an\nanalog input stream will look like the following:")]),t._v(" "),t._m(2),t._m(3),t._v(" "),t._m(4),t._v(" "),t._m(5),a("p",[t._v("As you can see, the loop didn't changed at all: the transformers are totally\ntransparent to you!")]),t._v(" "),a("p",[t._v("In "),a("router-link",{attrs:{to:"./InputStream_2.html"}},[t._v("Part 2")]),t._v(" we'll dig deeper into the available input streams.")],1)])},[function(){var t=this.$createElement,n=this._self._c||t;return n("h1",{attrs:{id:"io-inputstream-part1"}},[n("a",{staticClass:"header-anchor",attrs:{href:"#io-inputstream-part1","aria-hidden":"true"}},[this._v("#")]),this._v(" io::InputStream . Part1")])},function(){var t=this.$createElement,n=this._self._c||t;return n("p",[n("code",[this._v("InputStream")]),this._v(" is an abstract class to interact with, well, input streams!\nWhat are input streams, by the way? Simply put, an input stream is any thing\nthat generates values over time. Examples of input streams are an input pin\n(digital or analog) and any kind of sensor that returns a numeric value.")])},function(){var t=this,n=t.$createElement,a=t._self._c||n;return a("div",{staticClass:"language-c extra-class"},[a("pre",{pre:!0,attrs:{class:"language-c"}},[a("code",[t._v("AnalogInputStream "),a("span",{pre:!0,attrs:{class:"token function"}},[t._v("potentiometer")]),a("span",{pre:!0,attrs:{class:"token punctuation"}},[t._v("(")]),t._v("A0"),a("span",{pre:!0,attrs:{class:"token punctuation"}},[t._v(")")]),a("span",{pre:!0,attrs:{class:"token punctuation"}},[t._v(";")]),t._v("\n\n"),a("span",{pre:!0,attrs:{class:"token keyword"}},[t._v("void")]),t._v(" "),a("span",{pre:!0,attrs:{class:"token function"}},[t._v("setup")]),a("span",{pre:!0,attrs:{class:"token punctuation"}},[t._v("(")]),a("span",{pre:!0,attrs:{class:"token punctuation"}},[t._v(")")]),t._v(" "),a("span",{pre:!0,attrs:{class:"token punctuation"}},[t._v("{")]),t._v("\n    potentiometer"),a("span",{pre:!0,attrs:{class:"token punctuation"}},[t._v(".")]),a("span",{pre:!0,attrs:{class:"token function"}},[t._v("then")]),a("span",{pre:!0,attrs:{class:"token punctuation"}},[t._v("(")]),t._v("new "),a("span",{pre:!0,attrs:{class:"token function"}},[t._v("ExponentialSmoothing")]),a("span",{pre:!0,attrs:{class:"token punctuation"}},[t._v("(")]),a("span",{pre:!0,attrs:{class:"token number"}},[t._v("0.5")]),a("span",{pre:!0,attrs:{class:"token punctuation"}},[t._v(")")]),a("span",{pre:!0,attrs:{class:"token punctuation"}},[t._v(")")]),a("span",{pre:!0,attrs:{class:"token punctuation"}},[t._v(";")]),t._v("\n"),a("span",{pre:!0,attrs:{class:"token punctuation"}},[t._v("}")]),t._v("\n\n"),a("span",{pre:!0,attrs:{class:"token keyword"}},[t._v("void")]),t._v(" "),a("span",{pre:!0,attrs:{class:"token function"}},[t._v("loop")]),a("span",{pre:!0,attrs:{class:"token punctuation"}},[t._v("(")]),a("span",{pre:!0,attrs:{class:"token punctuation"}},[t._v(")")]),t._v(" "),a("span",{pre:!0,attrs:{class:"token punctuation"}},[t._v("{")]),t._v("\n    Serial"),a("span",{pre:!0,attrs:{class:"token punctuation"}},[t._v(".")]),a("span",{pre:!0,attrs:{class:"token function"}},[t._v("println")]),a("span",{pre:!0,attrs:{class:"token punctuation"}},[t._v("(")]),t._v("potentiomenter"),a("span",{pre:!0,attrs:{class:"token punctuation"}},[t._v(".")]),a("span",{pre:!0,attrs:{class:"token function"}},[t._v("read")]),a("span",{pre:!0,attrs:{class:"token punctuation"}},[t._v("(")]),a("span",{pre:!0,attrs:{class:"token punctuation"}},[t._v(")")]),a("span",{pre:!0,attrs:{class:"token punctuation"}},[t._v(")")]),a("span",{pre:!0,attrs:{class:"token punctuation"}},[t._v(";")]),t._v("\n"),a("span",{pre:!0,attrs:{class:"token punctuation"}},[t._v("}")]),t._v("\n")])])])},function(){var t=this.$createElement,n=this._self._c||t;return n("p",[this._v("Now, the input stream transparently takes care of managing its transformer,\nso you can just get the processed value with the "),n("code",[this._v("read()")]),this._v(" method. If you have\nset a transformer, it will transform your value, otherwise you'll get the raw\nvalue.")])},function(){var t=this.$createElement,n=this._self._c||t;return n("p",[this._v("Do you know what's the best part? Transformers are "),n("strong",[this._v("chainable")]),this._v(" 🔥🔥🔥"),n("br"),this._v("\nIf you want to map your smoothed potentiometer from [0, 1024] to [0, 100], for example,\nyou can chain a "),n("code",[this._v("Map")]),this._v(" transformer:")])},function(){var t=this,n=t.$createElement,a=t._self._c||n;return a("div",{staticClass:"language-c extra-class"},[a("pre",{pre:!0,attrs:{class:"language-c"}},[a("code",[t._v("AnalogPinInputStream "),a("span",{pre:!0,attrs:{class:"token function"}},[t._v("potentiometer")]),a("span",{pre:!0,attrs:{class:"token punctuation"}},[t._v("(")]),t._v("A0"),a("span",{pre:!0,attrs:{class:"token punctuation"}},[t._v(")")]),a("span",{pre:!0,attrs:{class:"token punctuation"}},[t._v(";")]),t._v("\n\n"),a("span",{pre:!0,attrs:{class:"token keyword"}},[t._v("void")]),t._v(" "),a("span",{pre:!0,attrs:{class:"token function"}},[t._v("setup")]),a("span",{pre:!0,attrs:{class:"token punctuation"}},[t._v("(")]),a("span",{pre:!0,attrs:{class:"token punctuation"}},[t._v(")")]),t._v(" "),a("span",{pre:!0,attrs:{class:"token punctuation"}},[t._v("{")]),t._v("\n    potentiometer\n        "),a("span",{pre:!0,attrs:{class:"token punctuation"}},[t._v(".")]),a("span",{pre:!0,attrs:{class:"token function"}},[t._v("then")]),a("span",{pre:!0,attrs:{class:"token punctuation"}},[t._v("(")]),t._v("new "),a("span",{pre:!0,attrs:{class:"token function"}},[t._v("ExponentialSmoothing")]),a("span",{pre:!0,attrs:{class:"token punctuation"}},[t._v("(")]),a("span",{pre:!0,attrs:{class:"token number"}},[t._v("0.5")]),a("span",{pre:!0,attrs:{class:"token punctuation"}},[t._v(")")]),a("span",{pre:!0,attrs:{class:"token punctuation"}},[t._v(")")]),t._v("\n        "),a("span",{pre:!0,attrs:{class:"token punctuation"}},[t._v(".")]),a("span",{pre:!0,attrs:{class:"token function"}},[t._v("then")]),a("span",{pre:!0,attrs:{class:"token punctuation"}},[t._v("(")]),t._v("new "),a("span",{pre:!0,attrs:{class:"token function"}},[t._v("Map")]),a("span",{pre:!0,attrs:{class:"token punctuation"}},[t._v("(")]),a("span",{pre:!0,attrs:{class:"token number"}},[t._v("0")]),a("span",{pre:!0,attrs:{class:"token punctuation"}},[t._v(",")]),t._v(" "),a("span",{pre:!0,attrs:{class:"token number"}},[t._v("1024")]),a("span",{pre:!0,attrs:{class:"token punctuation"}},[t._v(",")]),t._v(" "),a("span",{pre:!0,attrs:{class:"token number"}},[t._v("0")]),a("span",{pre:!0,attrs:{class:"token punctuation"}},[t._v(",")]),t._v(" "),a("span",{pre:!0,attrs:{class:"token number"}},[t._v("100")]),a("span",{pre:!0,attrs:{class:"token punctuation"}},[t._v(")")]),a("span",{pre:!0,attrs:{class:"token punctuation"}},[t._v(")")]),a("span",{pre:!0,attrs:{class:"token punctuation"}},[t._v(";")]),t._v("\n"),a("span",{pre:!0,attrs:{class:"token punctuation"}},[t._v("}")]),t._v("\n\n"),a("span",{pre:!0,attrs:{class:"token keyword"}},[t._v("void")]),t._v(" "),a("span",{pre:!0,attrs:{class:"token function"}},[t._v("loop")]),a("span",{pre:!0,attrs:{class:"token punctuation"}},[t._v("(")]),a("span",{pre:!0,attrs:{class:"token punctuation"}},[t._v(")")]),t._v(" "),a("span",{pre:!0,attrs:{class:"token punctuation"}},[t._v("{")]),t._v("\n    Serial"),a("span",{pre:!0,attrs:{class:"token punctuation"}},[t._v(".")]),a("span",{pre:!0,attrs:{class:"token function"}},[t._v("println")]),a("span",{pre:!0,attrs:{class:"token punctuation"}},[t._v("(")]),t._v("potentiomenter"),a("span",{pre:!0,attrs:{class:"token punctuation"}},[t._v(".")]),a("span",{pre:!0,attrs:{class:"token function"}},[t._v("read")]),a("span",{pre:!0,attrs:{class:"token punctuation"}},[t._v("(")]),a("span",{pre:!0,attrs:{class:"token punctuation"}},[t._v(")")]),a("span",{pre:!0,attrs:{class:"token punctuation"}},[t._v(")")]),a("span",{pre:!0,attrs:{class:"token punctuation"}},[t._v(";")]),t._v("\n"),a("span",{pre:!0,attrs:{class:"token punctuation"}},[t._v("}")]),t._v("\n")])])])}],!1,null,null,null);n.default=e.exports}}]);