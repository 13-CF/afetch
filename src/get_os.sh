#!/bin/sh

read -r OS KERNEL <<-EOF
	$(uname -sr)
EOF

get_os() {
    case $OS in
        Linux*)
            # Some Linux distributions (which are based on others)
            # fail to identify as they **do not** change the upstream
            # distribution's identification packages or files.
            #
            # It is senseless to add a special case in the code for
            # each and every distribution (which _is_ technically no
            # different from what it is based on) as they're either too
            # lazy to modify upstream's identification files or they
            # don't have the know-how (or means) to ship their own
            # lsb-release package.
            #
            # This causes users to think there's a bug in system detection
            # tools like neofetch or pfetch when they technically *do*
            # function correctly.
            #
            # Exceptions are made for distributions which are independent,
            # not based on another distribution or follow different
            # standards.
            #
            # This applies only to distributions which follow the standard
            # by shipping unmodified identification files and packages
            # from their respective upstreams.
            if command -v lsb_release; then
                DISTRO=$(lsb_release -sd)
    
            # Android detection works by checking for the existence of
            # the follow two directories. I don't think there's a simpler
            # method than this.
            elif [ -d /system/app ] && [ -d /system/priv-app ]; then
                DISTRO="Android $(getprop ro.build.version.release)"
    
            else
                # This used to be a simple '. /etc/os-release' but I believe
                # this is insecure as we blindly executed whatever was in the
                # file. This parser instead simply handles 'key=val', treating
                # the file contents as plain-text.
                while IFS='=' read -r key val; do
                    case $key in
                        PRETTY_NAME) DISTRO=$val ;;
                    esac
                done < /etc/os-release
            fi
    
            # 'os-release' and 'lsb_release' sometimes add quotes
            # around the distribution name, strip them.
            DISTRO=${DISTRO##[\"\']}
            DISTRO=${DISTRO%%[\"\']}
    
            # Special cases for (independent) distributions which
            # don't follow any os-release/lsb standards whatsoever.
            command -v crux && DISTRO=$(crux)
            command -v guix && DISTRO='Guix System'
    
            # Check to see if we're running Bedrock Linux which is
            # very unique. This simply checks to see if the user's
            # PATH contais a Bedrock specific value.
            case $PATH in
                */bedrock/cross/*) DISTRO='Bedrock Linux'
            esac
    
            # Check to see if Linux is running in Windows 10 under
            # WSL1 (Windows subsystem for Linux [version 1]) and
            # append a string accordingly.
            #
            # If the KERNEL version string ends in "-Microsoft",
            # we're very likely running under Windows 10 in WSL1.
            [ "${KERNEL%%*-Microsoft}" ] ||
                DISTRO="$DISTRO on Windows 10 [WSL1]"
    
            # Check to see if Linux is running in Windows 10 under
            # WSL2 (Windows subsystem for Linux [version 2]) and
            # append a string accordingly.
            #
            # This checks to see if '$WSLENV' is defined. This
            # appends the Windows 10 string even if '$WSLENV' is
            # empty. We only need to check that is has been _exported_.
            DISTRO="${DISTRO}${WSLENV+ on Windows 10 [WSL2]}"
        ;;
    
        Darwin*)
            # Parse the SystemVersion.plist file to grab the macOS
            # version. The file is in the following format:
            #
            # <key>ProductVersion</key>
            # <string>10.14.6</string>
            #
            # 'IFS' is set to '<>' to enable splitting between the
            # keys and a second 'read' is used to operate on the
            # next line directly after a match.
            #
            # '_' is used to nullify a field. '_ _ line _' basically
            # says "populate $line with the third field's contents".
            while IFS='<>' read -r _ _ line _; do
                case $line in
                    # Match 'ProductVersion' and read the next line
                    # directly as it contains the key's value.
                    ProductVersion)
                        IFS='<>' read -r _ _ mac_version _
                        break
                    ;;
                esac
            done < /System/Library/CoreServices/SystemVersion.plist
    
            # Use the ProductVersion to determine which macOS/OS X codename
            # the system has. As far as I'm aware there's no "dynamic" way
            # of grabbing this information.
            case $mac_version in
                10.4*)  DISTRO='Mac OS X Tiger' ;;
                10.5*)  DISTRO='Mac OS X Leopard' ;;
                10.6*)  DISTRO='Mac OS X Snow Leopard' ;;
                10.7*)  DISTRO='Mac OS X Lion' ;;
                10.8*)  DISTRO='OS X Mountain Lion' ;;
                10.9*)  DISTRO='OS X Mavericks' ;;
                10.10*) DISTRO='OS X Yosemite' ;;
                10.11*) DISTRO='OS X El Capitan' ;;
                10.12*) DISTRO='macOS Sierra' ;;
                10.13*) DISTRO='macOS High Sierra' ;;
                10.14*) DISTRO='macOS Mojave' ;;
                10.15*) DISTRO='macOS Catalina' ;;
                *)      DISTRO='macOS' ;;
            esac
    
            DISTRO="$DISTRO $mac_version"
        ;;
    
        Haiku)
            # Haiku uses 'uname -v' for version information
            # instead of 'uname -r' which only prints '1'.
            DISTRO=$(uname -sv)
        ;;
    
        Minix|DragonFly)
            DISTRO="$OS $KERNEL"
    
            # Minix and DragonFly don't support the escape
            # sequences used, clear the exit trap.
            trap '' EXIT
        ;;
    
        SunOS)
            # Grab the first line of the '/etc/release' file
            # discarding everything after '('.
            IFS='(' read -r DISTRO _ < /etc/release
        ;;
    
        *)
            # Catch all to ensure '$DISTRO' is never blank.
            # This also handles the BSDs.
            DISTRO="$OS"
        ;;
    esac
}

get_pkgs() {
    # This is just a simple wrapper around 'command -v' to avoid
    # spamming '>/dev/null' throughout this function.
    has() { command -v "$1" >/dev/null; }

    # This works by first checking for which package managers are
    # installed and finally by printing each package manager's
    # package list with each package one per line.
    #
    # The output from this is then piped to 'wc -l' to count each
    # line, giving us the total package count of whatever package
    # managers are installed.
    #
    # Backticks are *required* here as '/bin/sh' on macOS is
    # 'bash 3.2' and it can't handle the following:
    #
    # var=$(
    #    code here
    # )
    #
    PACKAGES=$(
        case $OS in
            Linux*)
                # Commands which print packages one per line.
                has bonsai     && printf "bonsai list"
                has crux       && printf "pkginfo -i"
                has pacman-key && printf "pacman -Qq"
                has dpkg       && printf "dpkg-query -f '.\\\\\\\n' -W"
                has rpm        && printf "rpm -qa"
                has xbps-query && printf "xbps-query -l"
                has apk        && printf "apk info"
                has guix       && printf "guix package --list-installed"
                has opkg       && printf "opkg list-installed"

                # Directories containing packages.
                has kiss       && printf "printf '%%s\\\\\\\n' /var/db/kiss/installed/*/"
                has brew       && printf "printf '%%s\\\\\\\n' \"\$(brew --cellar)/\"*"
                has emerge     && printf "printf '%%s\\\\\\\n' /var/db/pkg/*/*/"
                has pkgtool    && printf "printf '%%s\\\\\\\n' /var/log/packages/*"
                has eopkg      && printf "printf '%%s\\\\\\\n' /var/lib/eopkg/package/*"

                # 'nix' requires two commands.
                has nix-store  && {
                    printf "nix-store -q --requisites /run/current-system/sw"
                    printf "nix-store -q --requisites ~.nix-profile"
                }
            ;;

            Darwin*)
                # Commands which print packages one per line.
                has pkgin      && printf "pkgin list"

                # Directories containing packages.
                has brew       && printf "printf '%%s\\\\\\\n' /usr/local/Cellar/*"

                # 'port' prints a single line of output to 'stdout'
                # when no packages are installed and exits with
                # success causing a false-positive of 1 package
                # installed.
                #
                # 'port' should really exit with a non-zero code
                # in this case to allow scripts to cleanly handle
                # this behavior.
                has port       && {
                    pkg_list=$(port installed)

                    [ "$pkg_list" = "No ports are installed." ] ||
                        printf "printf '%%s\\\\\\\n' \"\$pkg_list\""
                }
            ;;

            FreeBSD*|DragonFly*)
                printf "pkg info"
            ;;

            OpenBSD*)
                printf "printf '%%s\\\\\\\n' /var/db/pkg/*/"
            ;;

            NetBSD*)
                printf "pkg_info"
            ;;

            Haiku)
                printf "printf '%%s\\\\\\\n' /boot/system/package-links/*"
            ;;

            Minix)
                printf "printf '%%s\\\\\\\n' /usr/pkg/var/db/pkg/*/"
            ;;

            SunOS)
                has pkginfo && printf "pkginfo -i"
                has pkg     && printf "pkg list"
            ;;

            IRIX)
                printf "versions -b"
            ;;
        esac
    )

    case $OS in
        # IRIX's package manager adds 3 lines of extra
        # output which we must account for here.
        IRIX) PACKAGES=$((PACKAGES - 3)) ;;
    esac
}


main() {
    get_os
    get_pkgs

    sed -i "s/.*#define DISTRO.*/#define DISTRO \"$DISTRO\"/" src/config.h
    sed -i "s/.*#define GET_PKG_CNT.*/#define GET_PKG_CNT \"$PACKAGES | wc -l\"/" src/config.h
    
    if grep -q "$DISTRO" src/distros.txt; then
        sed -i -e '/#define ASCII_ART/,+8d' src/config.h
        echo "#define ASCII_ART \\" >> src/config.h
        sed -n "/$DISTRO/,+8p" src/distros.txt | sed '1d' >> src/config.h
    fi
}

main
