#!/usr/bin/env python3
import argparse
import math
import random
from collections import deque

def distance(a, b):
    return math.hypot(a[0] - b[0], a[1] - b[1])

def build_graph(nodes, link_range, failed):
    graph = {i: [] for i in nodes if i not in failed}
    active = [i for i in nodes if i not in failed]
    for i in active:
        for j in active:
            if i < j and distance(nodes[i], nodes[j]) <= link_range:
                graph[i].append(j)
                graph[j].append(i)
    return graph

def shortest_path(graph, source, target):
    if source not in graph or target not in graph:
        return None
    q = deque([source])
    parent = {source: None}
    while q:
        u = q.popleft()
        if u == target:
            path = []
            while u is not None:
                path.append(u)
                u = parent[u]
            return path[::-1]
        for v in graph[u]:
            if v not in parent:
                parent[v] = u
                q.append(v)
    return None

def run(nodes_count, link_range, failed):
    random.seed(7)
    nodes = {i: (random.uniform(0, 500), random.uniform(0, 500))
             for i in range(nodes_count)}
    graph = build_graph(nodes, link_range, failed)
    source, target = 0, nodes_count - 1
    path = shortest_path(graph, source, target)
    print(f"nodes={nodes_count}, range={link_range}, failed={sorted(failed)}")
    print("source:", source, "target:", target)
    print("route:", path if path else "NO ROUTE")
    links = sum(len(v) for v in graph.values()) // 2
    print("active_links:", links)
    if path:
        hops = len(path) - 1
        delay_ms = hops * 2.0
        print("hops:", hops)
        print(f"estimated_delay_ms: {delay_ms:.2f}")
        print("packet_delivery_ratio: 100.00% (simulation route available)")
    else:
        print("packet_delivery_ratio: 0.00% (no route)")

def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--nodes", type=int, default=12)
    ap.add_argument("--range", type=float, default=180)
    ap.add_argument("--fail", type=int, nargs="*", default=[])
    args = ap.parse_args()
    if args.nodes < 2 or args.range <= 0:
        raise SystemExit("nodes must be >= 2 and range must be > 0")
    failed = {n for n in args.fail if 0 <= n < args.nodes}
    run(args.nodes, args.range, failed)

if __name__ == "__main__":
    main()
