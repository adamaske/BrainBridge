
from setuptools import setup, find_packages

with open('README.rst') as f:
    readme = f.read()

with open('LICENSE') as f:
    license = f.read()

setup(
    name='BrainBridge',
    version='0.1.0',
    description='Brain Bridge is an app',
    long_description=readme,
    author='Adam Aske',
    url='https://github.com/adamaske/brainbridge',
    license=license,
    packages=find_packages(exclude=('tests', 'docs'))
)