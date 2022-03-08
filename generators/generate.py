import os
from pathlib import Path

import sys
import getopt

TYPES = ["Configs"]
GENERATORS = {
    "Configs": {
        "name": "configsGenerator",
        "type": "Configs",
        "dir": "./configs",
        "data_dir": "./configs/data",
    },
    "Models":{
      "name":"modelsGenerator",
      "type": "Models",
      "dir": "./models",
    }
}


def main(argv):
    build_dir = ''
    update = False
    try:
        opts, args = getopt.getopt(argv, "s:bd:t", ["build-dir=", "update"])
    except getopt.GetoptError:
        print('generate.p -bd <build dir> -u')
        sys.exit(2)
    for opt, arg in opts:
        if opt == '-h':
            print('generate.py -bd <build dir> -u <update build>')
            sys.exit()
        elif opt in ("-bd", "--build-dir"):
            build_dir = arg
        elif opt in ("-u", "--update"):
            update = True

    print("Build directory:", build_dir)
    print("Need to update:", update)

    for name, info in GENERATORS.items():
        GENERATOR = info["name"]
        TYPE = info["type"]
        CONFIGS_FOLDER =info["data_dir"]  if "data_dir" in info else "" 

        FLAGS = ""
        FLAGS += "-s " if not update else ""
        FLAGS += "--skip-validate-spec " if TYPE == "Configs" else ""
        # FLAGS += " --skip-validate-spec"

        DIR = info["dir"]
        # TEST_INPUT = "https://raw.githubusercontent.com/openapitools/openapi-generator/master/modules/openapi-generator/src/test/resources/2_0/petstore.yaml"
        SCHEMAS_LIST = os.listdir(DIR+"/schemas")
        SCHEMAS_LIST = [schema for schema in SCHEMAS_LIST if Path(
            schema).suffix == '.yaml']

        SCHEMAS = ":::".join(
            [DIR+"/schemas/"+schema for schema in SCHEMAS_LIST])
        OUT = ":::".join(["{0}/codegen/{1}".format(build_dir, TYPE)
                         for schema in SCHEMAS_LIST])

        IMPL_FOLDER = "../../"+DIR
        COMPONENTS_FOLDER = "./"

        print("Schemas folder:", SCHEMAS_LIST)
        print("Output folder:", OUT)

        comand = ('export IMPL_FOLDER={4} && export CONFIGS_FOLDER={5} && export COMPONENTS_FOLDER={6} && \
                  java -cp generators/{0}.jar:generators/engine.jar   \
                  org.openapitools.codegen.OpenAPIGenerator generate \
                  -g {0} \
                  -i {1} \
                  -o {2} \
                  {3}').format(GENERATOR, SCHEMAS, OUT, FLAGS, IMPL_FOLDER, CONFIGS_FOLDER, COMPONENTS_FOLDER)

        print(comand)
        result = os.system(comand)
        if(result != 0):
            raise Exception("Codegen Error!")


if __name__ == "__main__":
    main(sys.argv[1:])
