import os
import re

class TestRunnerGenerator:
    def __init__(self):
        self.directory = os.getcwd()

    def find_test_groups(self, extension):
        test_groups = set()
        pattern = r'XTEST_DEFINE_POOL\((\w+)\)'

        for root, _, files in os.walk(self.directory):
            for file in files:
                if file.startswith('xtest_') and file.endswith('.' + extension):
                    with open(os.path.join(root, file), 'r') as f:
                        content = f.read()
                        matches = re.findall(pattern, content)
                        test_groups.update(matches)

        return list(test_groups)

    def generate_test_runner(self, test_groups, extension):
        header = """
// Generated Fossil Logic Test Runner
"""

        if extension == 'c':
            header += """
#include <fossil/xtest.h>

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test List
// * * * * * * * * * * * * * * * * * * * * * * * *"""
        elif extension == 'cpp':
            header += """
#include <fossil/xtest.h>

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test List
// * * * * * * * * * * * * * * * * * * * * * * * *"""
        elif extension == 'm':
            header += """
#import <fossil/xtest.h>

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test List
// * * * * * * * * * * * * * * * * * * * * * * * *"""
        elif extension == 'mm':
            header += """
#import <fossil/xtest.h>

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test List
// * * * * * * * * * * * * * * * * * * * * * * * *"""

        extern_pools = '\n'.join([f"XTEST_EXTERN_POOL({group});" for group in test_groups])

        runner = """
// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Runner
// * * * * * * * * * * * * * * * * * * * * * * * *
"""

        if extension == 'c':
            runner += """
int main(int argc, char **argv) {
    XTEST_CREATE(argc, argv);\n"""
        elif extension == 'cpp':
            runner += """
int main(int argc, char **argv) {
    XTEST_CREATE(argc, argv);\n"""
        elif extension == 'm':
            runner += """
int main(int argc, char **argv) {\n
    XTEST_CREATE(argc, argv);\n"""
        elif extension == 'mm':
            runner += """
int main(int argc, char **argv) {\n
    XTEST_CREATE(argc, argv);\n"""

        import_pools = '\n'.join([f"    XTEST_IMPORT_POOL({group});" for group in test_groups])

        footer = """
    return XTEST_ERASE();
} // end of func
"""

        with open(f'xunit_runner.{extension}', 'w') as file:
            file.write(header)
            file.write("\n")
            file.write(extern_pools)
            file.write(runner)
            file.write(import_pools)
            file.write("\n")
            file.write(footer)

# Example usage:
generator = TestRunnerGenerator()
extensions = ['c', 'cpp', 'm', 'mm']  # Add more extensions as needed
for ext in extensions:
    test_groups = generator.find_test_groups(ext)
    generator.generate_test_runner(test_groups, ext)
