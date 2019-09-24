const gData = {
    nodes: [
	{ id: 0, name: "(3,3,0)" },
	{ id: 1, name: "(3,2,0)" },
	{ id: 2, name: "(3,1,0)" },
	{ id: 10, name: "(2,3,0)", color: "red" },
	{ id: 11, name: "(2,2,0)" },
	{ id: 12, name: "(2,1,0)", color: "red" },
	{ id: 13, group: 133, name: "(2,0,0)", color: "red" },
	{ id: 20, name: "(1,3,0)", color: "red" },
	{ id: 21, name: "(1,2,0)", color: "red" },
	{ id: 22, group: 133, name: "(1,1,0)" },
	{ id: 23, group: 133, name: "(1,0,0)", color: "red" },
	{ id: 30, name: "(0,3,0)" },
	{ id: 31, group: 133, name: "(0,2,0)" },
	{ id: 32, group: 133, name: "(0,1,0)" },
	{ id: 102, name: "(0,2,1)" },
	{ id: 103, name: "(0,3,1)" },
	{ id: 111, name: "(1,1,1)" },
	{ id: 112, name: "(1,2,1)", color: "red" },
	{ id: 113, name: "(1,3,1)", color: "red" },
	{ id: 121, name: "(2,1,1)", color: "red" },
	{ id: 122, name: "(2,2,1)" },
	{ id: 123, name: "(2,3,1)", color: "red" },
	{ id: 131, name: "(3,1,1)" },
	{ id: 132, name: "(3,2,1)" },
	{ id: 133, name: "(3,3,1)" }
	],
    links: [
	 { target: 1, source: 102 },
	 { target: 1, source: 111 },
	 { target: 2, source: 103 },
	 { target: 11, source: 112 },
	 { target: 11, source: 113 },
	 { target: 11, source: 121 },
	 { target: 11, source: 122 },
	 { target: 22, source: 123 },
	 { target: 22, source: 132 },
	 { target: 30, source: 131 },
	 { target: 102, source: 0 },
	 { target: 103, source: 1 },
	 { target: 111, source: 10 },
	 { target: 122, source: 2 },
	 { target: 131, source: 11 },
	 { target: 131, source: 20 },
	 { target: 132, source: 12 },
	 { target: 132, source: 21 },
	 { target: 132, source: 30 },
	 { target: 133, source: 13 },
	 { target: 133, source: 22 },
	 { target: 133, source: 23 },
	 { target: 133, source: 31 },
	 { target: 133, source: 32 }
	]
};

const Graph = ForceGraph()
	(document.getElementById('graph'))
  	.graphData(gData);