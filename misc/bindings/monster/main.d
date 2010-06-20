module monster.main;

pragma(lib, "monster");
import monster.monster;

import monster.siege.siege;

class MNMain
{
    MonsterClass main;
    MonsterObject* maino;
    MNSiege siege;
    this()
    {
        vm.init();
        siege = new MNSiege;

        main = vm.load("monster.Main");
        maino = main.createObject();

        maino.call("main");
    }
}
