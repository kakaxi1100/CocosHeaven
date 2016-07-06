rd /s/q D:\keep\JuLi\Ares\project\CocosHeaven\popcandy\publish

@set path=D:\keep\JuLi\Ares\cocos2d-x-3.11.1\tools\cocos2d-console\bin;%path%
@set ANT_ROOT=D:\keep\JuLi\Ares\work\juli-PSHAENGDESK004-main\tools\apache-ant-1.9.7-bin\apache-ant-1.9.7\bin

call cocos compile -p web -m release --advanced

cmd