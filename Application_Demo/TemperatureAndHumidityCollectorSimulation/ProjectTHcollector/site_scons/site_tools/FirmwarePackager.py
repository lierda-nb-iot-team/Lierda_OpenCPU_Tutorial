#===============================================================================
# @brief    SCons tool for building firmware packages.
# Copyright (c) 2018 Huawei Technologies Co. Ltd
#===============================================================================

import json
import yaml
import os
import SCons.Action
import SCons.Builder

def create_manifest(env, target, source):
    manifest = target[0]
    contents = {}
    for s in source:
        if s.name.endswith(".bin"):
            key = "appsa"
        elif s.name.endswith(".yml"):
            key = "appskeyyaml"
        elif s.name.endswith(".etypes"):
            key = "appskeydsl"
        elif s.name.endswith(".json"):
            key = "memconfigfile"
        elif s.name.endswith(".sha256"):
            key = "appsa_signature_sha"
        else:
            raise SystemExit("Cannot package file: %s" % s.name)
        contents[key] = os.path.relpath(s.path, manifest.Dir(".").path)

    with open(manifest.path,'w') as f:
        yaml.dump(contents, f, default_flow_style=False)


def create_package_scanner(node, env, path, arg=None):
    contents = yaml.load(node.get_contents())
    manifestdir = os.path.dirname(node.path)
    sources = [node]
    if contents:
        for path in contents.values():
            sources.append(env.File(os.path.join(manifestdir, path)))
    return sources


def merge_memconfig(env, target, source):
    # merge common and application memory_config.json files
    configs = {}
    for s in source:
        contents = s.get_contents()
        try:
            config = json.loads(contents)
        except ValueError:
            print >>sys.stderr, "Error parsing json from '%s'" % s
            raise
        configs[s.name] = config

    common_memcfg = configs["apps_only_update_package_system_memory_config.json"]
    module_memcfg = configs["module_memory_config.json"]

    # Items are to be merged, the other sections are copied from one only
    items = []
    for config in [common_memcfg, module_memcfg]:
        for i in config["Items"]:
            if i not in items:
                items.append(i)
    merged_memconfig = {"Items": items}

    # pull out the other values from one file only
    for section in ["Application", "CPU", "Version", "Description"]:
        merged_memconfig[section] = common_memcfg[section]
    merged_memconfig["Platform"] = module_memcfg["Platform"]

    with open(target[0].path,'w') as f:
        json.dump(merged_memconfig, f)


def generate(env):
    env.Builder(
        action="#tools/FirmwarePackager/FirmwarePackager.exe",
    )

    MergeMemoryConfig = SCons.Builder.Builder(
        action=SCons.Action.Action(merge_memconfig, "$FWPKG_MEM_COMSTR")
    )

    CreatePackageManifest = SCons.Builder.Builder(
        action=SCons.Action.Action(create_manifest, "$FWPKG_MANIFEST_COMSTR"),
    )

    exe = env.File("#tools/FirmwarePackager/FirmwarePackager.exe")
    env["FWPKG_EXE"] = exe
    env["FWPKG_COM"] = "$FWPKG_EXE CreatePackage --codeloader $CODELOADER_VERSION $FWPKG_CODELOADER  --manifest $SOURCE  --out $TARGET"

    CreatePackage = SCons.Builder.Builder(
        action=SCons.Action.Action("$FWPKG_COM", "$FWPKG_COMSTR"),
        source_scanner=SCons.Scanner.Scanner(create_package_scanner),
    )
    env.Append(BUILDERS={
        "CreatePackageManifest": CreatePackageManifest,
        "CreatePackage": CreatePackage,
        "MergeMemoryConfig": MergeMemoryConfig,
    })


def exists(env):
    return True
