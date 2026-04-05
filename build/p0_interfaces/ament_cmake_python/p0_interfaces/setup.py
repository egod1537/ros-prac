from setuptools import find_packages
from setuptools import setup

setup(
    name='p0_interfaces',
    version='0.0.0',
    packages=find_packages(
        include=('p0_interfaces', 'p0_interfaces.*')),
)
