#!/bin/bash

DEFCONFIG="RM6877_defconfig"

make -j"$(nproc --all)" O=out ARCH=arm64 SUBARCH=arm64 "$DEFCONFIG"
cp -af out/.config arch/arm64/configs/"$DEFCONFIG"
git add arch/arm64/configs/"${DEFCONFIG}"
git commit -m "RM6877: defconfig: Regenerate"
echo -e "\nSuccessfully regenerated defconfig at $DEFCONFIG"
