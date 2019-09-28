const elem = document.getElementById('graph');

const Graph = ForceGraph()(elem)
	.graphData(gData)
	.centerAt(-50,50)
	.nodeRelSize(9)
	.linkWidth(5)
	.linkDirectionalParticles(2)
	.linkDirectionalArrowLength(6)
	.onNodeHover(node => elem.style.cursor = node ? 'pointer' : null);