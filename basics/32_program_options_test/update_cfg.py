import ConfigParser

def update_ini():
    cfg_parser = ConfigParser.RawConfigParser()
    cfg_parser.read("./integration_test.cfg")
    cfg_parser.set("case", "result_path", "result_222")
    with open("./integration_test.cfg", 'w+') as cfg_f:
        cfg_parser.write(cfg_f)

if __name__ == '__main__':
    update_ini()
