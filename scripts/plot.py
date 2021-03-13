from matplotlib import pyplot
from pathlib import Path
from typing import Dict


def plt(pior_caso_data: Dict[int, float], medio_caso_data: Dict[int, float]):
    figure = pyplot.figure()
    figure.suptitle("Tempo Execução BTree")

    subplot_pior_caso = figure.add_subplot(211)
    subplot_medio_caso = figure.add_subplot(212)

    subplot_pior_caso.set_title("Pior Caso")
    subplot_pior_caso.set_xlabel("Qtd Chaves (unit)")
    subplot_pior_caso.set_ylabel("Tempo Exucução (s)")

    subplot_medio_caso.set_title("Caso Médio")
    subplot_medio_caso.set_xlabel("Qtd Chaves (unit)")
    subplot_medio_caso.set_ylabel("Tempo Exucução (s)")

    subplot_pior_caso.plot(pior_caso_data.keys(), pior_caso_data.values())
    subplot_medio_caso.plot(medio_caso_data.keys(), medio_caso_data.values())

    pyplot.tight_layout()

    pyplot.savefig("./data/btree_exec_time.png")


def get_data(path: Path) -> Dict[int, float]:
    data = dict()
    with path.open("r") as data_file:
        data_lines = data_file.readlines()
    for data_line in data_lines:
        test, time_delta = data_line.split(" ")
        test = int(test)
        time_delta = float(time_delta)
        data[test] = time_delta
    return data


pior_caso_path = Path("./data/pior_caso.txt")
medio_caso_path = Path("./data/medio_caso.txt")

pior_caso_data = get_data(pior_caso_path)
medio_caso_data = get_data(medio_caso_path)
plt(pior_caso_data=pior_caso_data, medio_caso_data=medio_caso_data)
