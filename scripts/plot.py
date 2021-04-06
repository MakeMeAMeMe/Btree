from matplotlib import pyplot
from pathlib import Path
from typing import Dict


def plt(
        pior_caso_data_avl: Dict[int, float],
        medio_caso_data_avl: Dict[int, float],
        pior_caso_data_btree: Dict[int, float],
        medio_caso_data_btree: Dict[int, float]):
    figure = pyplot.figure(figsize=(15,10), dpi=80)
    figure.suptitle(f"Tempo Execução - BTree e AVL")

    subplot_pior_caso = figure.add_subplot(211)
    subplot_medio_caso = figure.add_subplot(212)

    subplot_pior_caso.set_title("Pior Caso")
    subplot_pior_caso.set_xlabel("Qtd Chaves (unit)")
    subplot_pior_caso.set_ylabel("Tempo Exucução (s)")

    subplot_medio_caso.set_title("Caso Médio")
    subplot_medio_caso.set_xlabel("Qtd Chaves (unit)")
    subplot_medio_caso.set_ylabel("Tempo Exucução (s)")

    subplot_pior_caso.plot(
        pior_caso_data_avl.keys(),
        pior_caso_data_avl.values(),
        label="AVL")
    subplot_pior_caso.plot(
        pior_caso_data_btree.keys(),
        pior_caso_data_btree.values(),
        label="BTree")

    subplot_medio_caso.plot(
        medio_caso_data_avl.keys(),
        medio_caso_data_avl.values(),
        label="AVL")
    subplot_medio_caso.plot(
        medio_caso_data_btree.keys(),
        medio_caso_data_btree.values(),
        label="BTree")

    # pyplot.tight_layout()
    
    subplot_pior_caso.legend()
    subplot_medio_caso.legend()
    
    pyplot.savefig(f"./data/avl_btree_exec_time.svg")
    pyplot.savefig(f"./data/avl_btree_exec_time.png")


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


pior_caso_avl_path = Path("./data/avl/pior_caso.txt")
medio_caso_avl_path = Path("./data/avl/medio_caso.txt")
pior_caso_btree_path = Path("./data/btree/pior_caso.txt")
medio_caso_btree_path = Path("./data/btree/medio_caso.txt")

pior_caso_avl_data = get_data(pior_caso_avl_path)
medio_caso_avl_data = get_data(medio_caso_avl_path)
pior_caso_btree_data = get_data(pior_caso_btree_path)
medio_caso_btree_data = get_data(medio_caso_btree_path)

plt(
    pior_caso_data_avl=pior_caso_avl_data,
    medio_caso_data_avl=medio_caso_avl_data,
    pior_caso_data_btree=pior_caso_btree_data,
    medio_caso_data_btree=medio_caso_btree_data
)
