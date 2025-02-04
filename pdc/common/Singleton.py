import logging
logger = logging.getLogger(__name__)

class Singleton(object):
    def __new__(cls):
        logger.debug(f"Get {cls} singleton")
        if not hasattr(cls, 'instance'):
            logger.debug(f"Create a {cls} instance")
            cls.instance = super(Singleton, cls).__new__(cls)
        return cls.instance