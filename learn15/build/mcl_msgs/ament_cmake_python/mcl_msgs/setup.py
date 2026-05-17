from setuptools import find_packages
from setuptools import setup

setup(
    name='mcl_msgs',
    version='0.0.0',
    packages=find_packages(
        include=('mcl_msgs', 'mcl_msgs.*')),
)
