const elem = document.getElementById('graph');

const Graph = ForceGraph()(elem)
	.graphData(gData)
	.width(480)
	.height(480)
	.nodeRelSize(4)
	.linkWidth(2)
	.linkDirectionalParticles(2)
	.linkDirectionalArrowLength(6)
	.dagMode('td')
	.dagLevelDistance(30)
	.onNodeHover(node => elem.style.cursor = node ? 'pointer' : null);