# Light Wave Laser Mesh Network for Disaster Communication

A software simulation of a laser / free-space-optical (FSO) mesh network designed for emergency communication when conventional infrastructure is unavailable.

## Features
- Configurable network nodes
- Distance-based FSO links
- Node failure simulation
- Shortest-path routing
- Route recovery after node failure
- Packet delivery simulation
- Basic throughput, delay and delivery-ratio metrics
- Command-line simulation output

## Technologies
- Python 3
- Standard Python library

## Run
```bash
python3 src/lightweave.py
```

Optional:
```bash
python3 src/lightweave.py --nodes 12 --range 180 --fail 5
```

## Validation
The simulator validates:
- Link creation only within configured range
- Disconnected nodes
- Route availability
- Node-failure recovery
- Packet delivery accounting

This repository is a software simulation. It does not claim physical laser-hardware validation.

## Future Improvements
- Folium/OpenStreetMap visualization
- NS-3 integration
- Physical FSO transceiver interface
- More detailed optical link budget
- Energy model
