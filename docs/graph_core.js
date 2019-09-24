const elem = document.getElementById('graph');

const Graph = ForceGraph()(elem)
	.graphData(gData)
	.nodeRelSize(9)
	.linkWidth(5)
	.linkDirectionalParticles(1)
	.linkDirectionalArrowLength(6)
	.onNodeHover(node => elem.style.cursor = node ? 'pointer' : null);