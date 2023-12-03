import sys

def vertices(obj_path: str):
    code = "float vertices[] = {{{}}};"
    vertice_list = []
    with open(obj_path, "r") as f:
        count = 0
        for l in f.read().splitlines():
            if not l.startswith("v "):
                continue
            

            x, y, z = map(lambda x: float(x) / 2.0, l.split(" ")[1:])
            vertice_list.append(f"{x / 2.0}, {y / 2.0}, {z / 2.0}, {x}, {y},")
            count += 1
        print (count)
    return code.format("".join(vertice_list))
    
if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Expects .obj file as only argument!")
        sys.exit(-1)
    obj_path = sys.argv[1]
    with open("vertices.cpp", "w") as f:
        f.write(vertices(obj_path))