import os
import re

class TestRunnerGenerator:
    def __init__(self):
        self.directory = os.getcwd()

    def find_test_groups(self):
        test_groups = set()
        pattern = r'XTEST_DEFINE_POOL\((\w+)\)'

        for root, _, files in os.walk(self.directory):
            for file in files:
                if file.startswith('xtest_') and file.endswith('.c'):
                    with open(os.path.join(root, file), 'r') as f:
                        content = f.read()
                        matches = re.findall(pattern, content)
                        test_groups.update(matches)

        return list(test_groups)

    def generate_test_runner(self, test_groups):
        header = """/*
    ==========================================================================
    Author: Michael Gene Brockus (Dreamer)
    Email: michaelbrockus@gmail.com
    Organization: Fossil Logic
    Description: 
        This file is part of the Fossil Logic project, where innovation meets
        excellence in software development. Michael Gene Brockus, also known as
        "Dreamer," is a dedicated contributor to this project. For any inquiries,
        feel free to contact Michael at michaelbrockus@gmail.com.
    ==========================================================================
    */
    // Generated Fossil Logic Test

    #include <fossil/xtest.h>

    //
    // XUNIT-GROUP: list of test groups for the runner
    //"""

        extern_pools = '\n'.join([f"XTEST_EXTERN_POOL({group});" for group in test_groups])

        runner = """
    //
    // XUNIT-TEST RUNNER:
    //
    int main(int argc, xstring *argv) {
        XTEST_CREATE(argc, argv);\n"""

        import_pools = '\n'.join([f"    XTEST_IMPORT_POOL({group});" for group in test_groups])

        footer = """
        return XTEST_ERASE();
    } // end of func"""

        with open('xunit_runner.c', 'w') as file:
            file.write(header)
            file.write("\n")
            file.write(extern_pools)
            file.write(runner)
            file.write(import_pools)
            file.write("\n")
            file.write(footer)

# Example usage:
generator = TestRunnerGenerator()
test_groups = generator.find_test_groups()
generator.generate_test_runner(test_groups)
