case Alpine_Linux:
    inf->col1          = BBLUE "";
    inf->col2          = BBLUE "     /\\ /\\    ";
    inf->col3          = BBLUE "    /  \\  \\   ";
    inf->col4          = BBLUE "   /    \\  \\  ";
    inf->col5          = BBLUE "  /      \\  \\ ";
    inf->col6          = BBLUE " /        \\  \\";
    inf->col7          = BBLUE "           \\  ";
    inf->col8          = BBLUE "              ";
    inf->get_pkg_count = "grep 'P:' /lib/apk/db/installed | wc -l";
    break;
case Arch_Linux:
    inf->col1          = BCYAN "";
    inf->col2          = BCYAN "       /\\      ";
    inf->col3          = BCYAN "      /  \\     ";
    inf->col4          = BCYAN "     /\\   \\    ";
    inf->col5          = BBLUE "    /      \\   ";
    inf->col6          = BBLUE "   /   ,,   \\  ";
    inf->col7          = BBLUE "  /   |  |  -\\ ";
    inf->col8          = BBLUE " /_-''    ''-_\\";
    inf->get_pkg_count = "pacman -Qq | wc -l";
    break;
case Arch_bang_Linux:
    inf->col1          = BCYAN "           ____\n";
    inf->col2          = BCYAN "       /\\ /   /";
    inf->col3          = BCYAN "      /  /   / ";
    inf->col4          = BCYAN "     /   / /   ";
    inf->col5          = BCYAN "    /   /_/\\   ";
    inf->col6          = BCYAN "   /   __   \\  ";
    inf->col7          = BCYAN "  /   /_/\\   \\ ";
    inf->col8          = BCYAN " /_-''    ''-_\\";
    inf->get_pkg_count = "pacman -Qq | wc -l";
    break;
case ArcoLinux:
    inf->col1          = BBLUE "";
    inf->col2          = BBLUE "       /\\      ";
    inf->col3          = BBLUE "      /  \\     ";
    inf->col4          = BBLUE "     / /\\ \\    ";
    inf->col5          = BBLUE "    / /  \\ \\   ";
    inf->col6          = BBLUE "   / /    \\ \\  ";
    inf->col7          = BBLUE "  / / _____\\ \\ ";
    inf->col8          = BBLUE " /_/  `----.\\_\\";
    inf->get_pkg_count = "pacman -Qq | wc -l";
    break;
case Artix_Linux:
    inf->col1          = BCYAN "";
    inf->col2          = BCYAN "       /\\      ";
    inf->col3          = BCYAN "      /  \\     ";
    inf->col4          = BCYAN "     /`'.,\\    ";
    inf->col5          = BCYAN "    /     ',   ";
    inf->col6          = BCYAN "   /      ,`\\  ";
    inf->col7          = BCYAN "  /   ,.'`.  \\ ";
    inf->col8          = BCYAN " /.,'`     `'.\\";
    inf->get_pkg_count = "pacman -Qq | wc -l";
    break;
case CelOS:
    inf->col1 = BMAGENTA "";
    inf->col2 = BMAGENTA "      ______     ";
    inf->col3 =
        BMAGENTA "    _-" BWHITE " _____" BMAGENTA "\\" BWHITE " __ " BMAGENTA;
    inf->col4 = BMAGENTA "   -         -   ";
    inf->col5 = BWHITE " __" BMAGENTA "|" BWHITE "_____" BMAGENTA "     |  ";
    inf->col6 = BMAGENTA "   |          |  ";
    inf->col7 =
        BMAGENTA "   -_" BWHITE "  ______" BMAGENTA "/" BWHITE "_  " BMAGENTA;
    inf->col8 = BMAGENTA "     -______/    ";
    // have to add support for flatpak too
    inf->get_pkg_count = "dpkg -l | tail -n+6 | wc -l";
    break;
case Deepin:
    /* TO DO: CREATE DEEPIN LOGO */
    // inf->col1        = BRED "";
    // inf->col2        = BRED "";
    // inf->col3        = BRED "";
    // inf->col4        = BRED "";
    // inf->col5        = BRED "";
    // inf->col6        = BRED "";
    // inf->col7        = BRED "";
    // inf->col8        = BRED "";
    inf->get_pkg_count = "dpkg -l | tail -n+6 | wc -l";
    break;
case Debian_GNU_Linux:
    inf->col1          = BRED "";
    inf->col2          = BRED "   _____  ";
    inf->col3          = BRED "  /  __ \\ ";
    inf->col4          = BRED " |  /    |";
    inf->col5          = BRED " |  \\___- ";
    inf->col6          = BRED " -_       ";
    inf->col7          = BRED "   --_    ";
    inf->col8          = BRED "          ";
    inf->get_pkg_count = "dpkg -l | tail -n+6 | wc -l";
    break;
case Arch7:
    inf->col1          = BCYAN "";
    inf->col2          = BCYAN "  _______      ";
    inf->col3          = BCYAN " |____   \\     ";
    inf->col4          = BCYAN "     / /\\ \\    ";
    inf->col5          = BCYAN "    / /__\\ \\   ";
    inf->col6          = BCYAN "   / /____\\ \\  ";
    inf->col7          = BCYAN "  /_/      \\_\\ ";
    inf->col8          = BCYAN "               ";
    inf->get_pkg_count = "pacman -Qq | wc -l";
    break;
case elementary_OS:
    inf->col1          = BCYAN "";
    inf->col2          = BCYAN "   _______  ";
    inf->col3          = BCYAN "  / ____  \\ ";
    inf->col4          = BCYAN " /  |  /  /\\";
    inf->col5          = BCYAN " |__\\ /  / |";
    inf->col6          = BCYAN " \\   /__/  /";
    inf->col7          = BCYAN "  \\_______/ ";
    inf->col8          = BCYAN "            ";
    inf->get_pkg_count = "dpkg -l | tail -n+6 | wc -l";
    break;
case EndeavourOS:
    inf->col1          = BCYAN "";
    inf->col2          = BRED "       /" BBLUE "\\     " BCYAN;
    inf->col3          = BRED "     /" BBLUE "/  \\" BCYAN "\\   " BCYAN;
    inf->col4          = BRED "    /" BBLUE "/    \\ " BCYAN "\\ " BCYAN;
    inf->col5          = BRED "  / " BBLUE "/     _) " BCYAN ")" BCYAN;
    inf->col6          = BRED " /_" BBLUE "/___-- " BCYAN "__- " BCYAN;
    inf->col7          = BCYAN "  /____--     " BCYAN;
    inf->col8          = BCYAN "              ";
    inf->get_pkg_count = "pacman -Qq | wc -l";
    break;
case Fedora:
    inf->col1          = BWHITE "       _____\n" BBLUE;
    inf->col2          = BWHITE "      /   __)" BBLUE "\\ ";
    inf->col3          = BWHITE "      |  /  " BBLUE "\\ \\";
    inf->col4          = BWHITE "   ___|  |" BBLUE "__/ /";
    inf->col5          = BBLUE "  / " BWHITE "(_    _)" BBLUE "_/ ";
    inf->col6          = BBLUE " / /  " BWHITE "|  |     " BBLUE;
    inf->col7          = BBLUE " \\ \\" BWHITE "__/  |     " BBLUE;
    inf->col8          = BBLUE "  \\" BWHITE "(_____/     " BBLUE;
    inf->get_pkg_count = "[[ $(which sqlite3 2>/dev/null) && $? -ne "
                         "1 ]] && (sqlite3 "
                         "/var/lib/rpm/rpmdb.sqlite \"select * from "
                         "Name\"|wc -l) || rpm -qa | wc -l";
    break;
case Gentoo:
    inf->col1          = BWHITE "";
    inf->col2          = BMAGENTA "   _-----_   ";
    inf->col3          = BMAGENTA "  (       \\  ";
    inf->col4          = BMAGENTA "  \\    0   \\ ";
    inf->col5          = BMAGENTA "   \\        )";
    inf->col6          = BMAGENTA "   /      _/ ";
    inf->col7          = BMAGENTA "  (     _-   ";
    inf->col8          = BMAGENTA "  \\____-     ";
    inf->get_pkg_count = "qlist -IRv | wc -l";
    break;
case KDE_neon:
    inf->col1          = BGREEN "";
    inf->col2          = BGREEN "            ";
    inf->col3          = BGREEN "     --- _  ";
    inf->col4          = BGREEN "  /  ---  \\ ";
    inf->col5          = BGREEN " |  |   |  |";
    inf->col6          = BGREEN "  \\  --- _/ ";
    inf->col7          = BGREEN "     ---    ";
    inf->col8          = BGREEN "            ";
    inf->get_pkg_count = "dpkg -l | tail -n+6 | wc -l";
    break;
case Linux_Mint:
    inf->col1          = BGREEN "";
    inf->col2          = BGREEN "   _____________   ";
    inf->col3          = BGREEN "  |_            \\  ";
    inf->col4          = BGREEN "   |  | _____  |   ";
    inf->col5          = BGREEN "   |  | | | |  |   ";
    inf->col6          = BGREEN "   |  | | | |  |   ";
    inf->col7          = BGREEN "   |  \\_____/  |   ";
    inf->col8          = BGREEN "   \\___________/   ";
    inf->get_pkg_count = "dpkg -l | tail -n+6 | wc -l";
    break;
case Manjaro:
    inf->col1          = BGREEN "  ________  __ \n";
    inf->col2          = BGREEN " |       | |  |";
    inf->col3          = BGREEN " |   ____| |  |";
    inf->col4          = BGREEN " |  |  __  |  |";
    inf->col5          = BGREEN " |  | |  | |  |";
    inf->col6          = BGREEN " |  | |  | |  |";
    inf->col7          = BGREEN " |  | |  | |  |";
    inf->col8          = BGREEN " |__| |__| |__|";
    inf->get_pkg_count = "pacman -Qq | wc -l";
    break;
case NixOS:
    inf->col1          = BMAGENTA "";
    inf->col2          = BMAGENTA "   \\\\  \\\\ //  ";
    inf->col3          = BMAGENTA "  ==\\\\__\\\\/ //";
    inf->col4          = BMAGENTA "    //   \\\\// ";
    inf->col5          = BMAGENTA " ==//     //==";
    inf->col6          = BMAGENTA "  //\\\\___//   ";
    inf->col7          = BMAGENTA " // /\\\\  \\\\== ";
    inf->col8          = BMAGENTA "   // \\\\  \\\\  ";
    inf->get_pkg_count = "nix-store -q --requisites "
                         "/run/current-system/sw | wc -l";
    break;
case openSUSE_Leap:
case openSUSE_Tumbleweed:
    inf->col1          = BGREEN "";
    inf->col2          = BGREEN "   _______  ";
    inf->col3          = BGREEN " __|   __ \\ ";
    inf->col4          = BGREEN "      / .\\ \\";
    inf->col5          = BGREEN "      \\__/ |";
    inf->col6          = BGREEN "    _______|";
    inf->col7          = BGREEN "    \\_______";
    inf->col8          = BGREEN " __________/";
    inf->get_pkg_count = "rpm -qa | wc -l";
    break;
case Parabola:
    inf->col1          = BMAGENTA "";
    inf->col2          = BMAGENTA "   __ __ __  _  ";
    inf->col3          = BMAGENTA " .`_//_//_/ / `.";
    inf->col4          = BMAGENTA "           /  .`";
    inf->col5          = BMAGENTA "          / .`  ";
    inf->col6          = BMAGENTA "         /.`    ";
    inf->col7          = BMAGENTA "        /`      ";
    inf->col8          = BMAGENTA "                ";
    inf->get_pkg_count = "pacman -Qq | wc -l";
    break;
case Pop_OS:
    inf->col1          = BCYAN " ______\n";
    inf->col2          = BCYAN " \\   _ \\        __";
    inf->col3          = BCYAN "  \\ \\ \\ \\      / /";
    inf->col4          = BCYAN "   \\ \\_\\ \\    / / ";
    inf->col5          = BCYAN "    \\  ___\\  /_/  ";
    inf->col6          = BCYAN "     \\ \\    _     ";
    inf->col7          = BCYAN "    __\\_\\__(_)_   ";
    inf->col8          = BCYAN "   (___________)  ";
    inf->get_pkg_count = "dpkg -l | tail -n+6 | wc -l";
    break;
case postmarketOS:
    inf->col1          = BGREEN "        /\\       \n";
    inf->col2          = BGREEN "       /  \\      ";
    inf->col3          = BGREEN "      /    \\     ";
    inf->col4          = BGREEN "     /\\__   \\    ";
    inf->col5          = BGREEN "    /   /\\  _\\   ";
    inf->col6          = BGREEN "   /   ___\\/  \\  ";
    inf->col7          = BGREEN "  /    \\       \\ ";
    inf->col8          = BGREEN " /_____/________\\";
    inf->get_pkg_count = "grep 'P:' /lib/apk/db/installed | wc -l";
    break;
case Slackware:
    inf->col1          = BBLUE "";
    inf->col2          = BBLUE "    ________  ";
    inf->col3          = BBLUE "   /  ______| ";
    inf->col4          = BBLUE "   | |______  ";
    inf->col5          = BBLUE "   \\______  \\ ";
    inf->col6          = BBLUE "    ______| | ";
    inf->col7          = BBLUE " | |________/ ";
    inf->col8          = BBLUE " |____________";
    inf->get_pkg_count = "ls /var/log/packages | wc -l";
    break;
case Solus:
    inf->col1          = BMAGENTA "     __________\n";
    inf->col2          = BMAGENTA "    /          \\   ";
    inf->col3          = BMAGENTA "   /   /\\ \\     \\  ";
    inf->col4          = BMAGENTA "  /   /  \\ \\     \\ ";
    inf->col5          = BMAGENTA " |   /    \\ \\     |";
    inf->col6          = BMAGENTA "  \\--------------/ ";
    inf->col7          = BMAGENTA "   \\------------/  ";
    inf->col8          = BMAGENTA "    \\----------/   ";
    inf->get_pkg_count = "ls /var/lib/eopkg/package/ | wc -l";
    break;
case Ubuntu:
    inf->col1          = BRED "";
    inf->col2          = BRED "          _  ";
    inf->col3          = BRED "      ---(_) ";
    inf->col4          = BRED "  _/  ---  \\ ";
    inf->col5          = BRED " (_) |   |   ";
    inf->col6          = BRED "   \\  --- _/ ";
    inf->col7          = BRED "      ---(_) ";
    inf->col8          = BRED "             ";
    inf->get_pkg_count = "dpkg -l | tail -n+6 | wc -l";
    break;
case Void:
    inf->col1          = BGREEN "      _____\n";
    inf->col2          = BGREEN "   _  \\____ -  ";
    inf->col3          = BGREEN "  / / ____ \\ \\ ";
    inf->col4          = BGREEN " / / /    \\ \\ \\";
    inf->col5          = BGREEN " | |  " BGRAY BITAL "VOID  " BGREEN "| |";
    inf->col6          = BGREEN " \\ \\ \\____/ / /";
    inf->col7          = BGREEN "  \\ \\____  /_/ ";
    inf->col8          = BGREEN "   -_____\\     ";
    inf->get_pkg_count = "xbps-query -l | wc -l";
    break;
case Zorin_OS:
    inf->col1          = BBLUE "";
    inf->col2          = BBLUE "    ______    ";
    inf->col3          = BBLUE "   /______\\  ";
    inf->col4          = BBLUE "  /      / \\ ";
    inf->col5          = BBLUE " /      /   \\";
    inf->col6          = BBLUE " \\     /    /";
    inf->col7          = BBLUE "  \\   /___ / ";
    inf->col8          = BBLUE "   \\______/  ";
    inf->get_pkg_count = "dpkg -l | tail -n+6 | wc -l";
    break;
