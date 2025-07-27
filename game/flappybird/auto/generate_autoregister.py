import json

with open('components.txt') as f:
    components = [line.strip() for line in f if line.strip()]

with open('systems.json') as f:
    systems = json.load(f)

all_systems = [s['name'] for s in systems]
all_components = set(components)
for s in systems:
    all_components.update(s['components'])

with open('AutoRegister.cpp', 'w') as f:
    f.write('#include "Registry.hpp"\n')
    f.write('#include "Engine.hpp"\n')
    for c in sorted(all_components):
        f.write(f'#include "{c}.hpp"\n')
    for s in all_systems:
        f.write(f'#include "{s}.hpp"\n')
    f.write('\nvoid autoRegister(Registry& registry, Engine& engine) {\n')
    for c in sorted(all_components):
        f.write(f'    registry.registerComponent<{c}>();\n')
    f.write('\n')
    for s in systems:
        str = f"    engine.registerSystem<{s['name']}, "+ ', '.join(s['components']) + '>();\n'
        f.write(str)
    f.write('}\n')