#
# Generate OC-Yang struct file
# -path: depends modules' path, seperated by comma
# $OC_MODULES: modules to be generated
#

OC_PATH='./public/release/models'
IETF_PATH='./public/third_party/ietf'
LOCAL_PATH='./public/release/models'

OC_MODULES=$(ls ./public/release/models/*/*.yang )

go run ../../github/ygot/generator/generator.go \
  -path=public\
  -output_file=./ocstruct/oc.go \
  -package_name=ocstruct -generate_fakeroot -fakeroot_name=device -compress_paths=true \
  -shorten_enum_leaf_names \
  -trim_enum_openconfig_prefix \
  -typedef_enum_with_defmod \
  -enum_suffix_for_simple_union_enums \
  -exclude_modules=ietf-interfaces \
  -generate_leaf_getters \
  -generate_simple_unions \
  -list_builder_key_threshold=3 \
  $OC_MODULES

gofmt -w -s ./ocsturct/oc.go

# pyang \
#         -f jstree \
#         -o ./ocstruct_tree.html \
#         -p $OC_PATH:$IETF_PATH \
#         $OC_MODULES

# pyang \
#         -f tree \
#         -o ./ocstruct_tree.tree \
#         -p $OC_PATH:$IETF_PATH \
#         $OC_MODULES
