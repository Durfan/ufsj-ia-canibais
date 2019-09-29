const gData = {
	nodes: [
	{ id: 31, name: "(3,3,1)", color: "green" },
	{ id: 30, name: "(3,2,1)" },
	{ id: 29, name: "(3,1,1)" },
	{ id: 27, name: "(2,3,1)", color: "red" },
	{ id: 26, name: "(2,2,1)" },
	{ id: 25, name: "(2,1,1)", color: "red" },
	{ id: 23, name: "(1,3,1)", color: "red" },
	{ id: 22, name: "(1,2,1)", color: "red" },
	{ id: 21, name: "(1,1,1)" },
	{ id: 19, name: "(0,3,1)" },
	{ id: 18, name: "(0,2,1)" },
	{ id: 14, name: "(0,1,0)" },
	{ id: 13, name: "(0,2,0)" },
	{ id: 12, name: "(0,3,0)" },
	{ id: 11, name: "(1,0,0)", color: "red" },
	{ id: 10, name: "(1,1,0)" },
	{ id: 9, name: "(1,2,0)", color: "red" },
	{ id: 8, name: "(1,3,0)", color: "red" },
	{ id: 7, name: "(2,0,0)", color: "red" },
	{ id: 6, name: "(2,1,0)", color: "red" },
	{ id: 5, name: "(2,2,0)" },
	{ id: 4, name: "(2,3,0)", color: "red" },
	{ id: 2, name: "(3,1,0)" },
	{ id: 1, name: "(3,2,0)" },
	{ id: 0, name: "(3,3,0)", color: "green" },
	],
	links: [
	{ target: 18, source: 1, name: "0,1" },
	{ target: 21, source: 1, name: "1,0" },
	{ target: 19, source: 2, name: "0,1" },
	{ target: 22, source: 5, name: "0,1" },
	{ target: 23, source: 5, name: "0,2" },
	{ target: 25, source: 5, name: "1,0" },
	{ target: 26, source: 5, name: "1,1" },
	{ target: 27, source: 10, name: "0,1" },
	{ target: 29, source: 12, name: "0,1" },
	{ target: 30, source: 13, name: "0,1" },
	{ target: 1, source: 19, name: "0,2" },
	{ target: 0, source: 21, name: "1,1" },
	{ target: 4, source: 21, name: "0,1" },
	{ target: 2, source: 26, name: "2,0" },
	{ target: 5, source: 29, name: "2,0" },
	{ target: 8, source: 29, name: "1,1" },
	{ target: 6, source: 30, name: "2,0" },
	{ target: 9, source: 30, name: "1,1" },
	{ target: 12, source: 30, name: "0,2" },
	{ target: 7, source: 31, name: "2,0" },
	{ target: 10, source: 31, name: "1,1" },
	{ target: 11, source: 31, name: "1,0" },
	{ target: 13, source: 31, name: "0,2" },
	{ target: 14, source: 31, name: "0,1" },
	]
};

$('span.memoria').text('25');

$('span.tempo').text('0.000635s');