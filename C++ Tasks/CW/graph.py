import graphviz
import json
import os
import sys

def parse_input_file(input_file):
    ext = os.path.splitext(input_file)[1].lower()
    edges = []

    if ext == '.json':
        with open(input_file, 'r') as f:
            data = json.load(f)

        if not isinstance(data.get('edges'), list):
            raise ValueError("JSON must contain an 'edges' array")

        for edge in data['edges']:
            if not isinstance(edge, list) or len(edge) != 2:
                raise ValueError("Each edge must be an array of two vertices")

            u, v = map(int, edge)
            edges.append((u, v))
    else:
        with open(input_file, 'r') as f:
            lines = f.readlines()

        for line in lines[1:]:
            u, v = map(int, line.strip().split())
            edges.append((u, v))

    return edges

def parse_bridges_file(file_path):
    if file_path is None or not os.path.exists(file_path):
        return set()
    
    bridges = set()
    with open(file_path, 'r') as f:
        for line in f:
            u, v = map(int, line.strip().split())
            bridges.add((min(u, v), max(u, v)))

    return bridges

def parse_articulation_file(file_path):
    if file_path is None or not os.path.exists(file_path):
        return set()
    
    articulation = set()
    with open(file_path, 'r') as f:
        line = f.readline().strip()
        if line:
            articulation = {int(x) for x in line.split(',')}
    return articulation

def render_graph(input_file, bridges_file=None, articulation_file=None, output_file='graph', fmt='png'):
    edges = parse_input_file(input_file)
    bridges = parse_bridges_file(bridges_file)
    articulation = parse_articulation_file(articulation_file)

    g = graphviz.Graph('G', format=fmt)

    nodes = set()
    for u, v in edges:
        nodes.add(u)
        nodes.add(v)

    for node in nodes:
        if node in articulation:
            g.node(str(node), color='deeppink', style='filled', fillcolor='mistyrose')
        else:
            g.node(str(node))

    for u, v in edges:
        if (min(u, v), max(u, v)) in bridges:
            g.edge(str(u), str(v), color='cyan', penwidth='2')
        else:
            g.edge(str(u), str(v))

    g.render(output_file, view=True)
    print(f"Graph saved as {output_file}.{fmt}")

def main():
    try:
        if len(sys.argv) == 2:
            render_graph(sys.argv[1])  # Only input file, no color
        elif len(sys.argv) == 4:
            render_graph(sys.argv[1], sys.argv[2], sys.argv[3])
        else:
            print("Usage:")
            print("  python3 graph.py input.txt")
            print("  python3 graph.py input.txt bridges.txt articulation.txt")
    except Exception as e:
        print(f"Error: {e}")

if __name__ == "__main__":
    main()
