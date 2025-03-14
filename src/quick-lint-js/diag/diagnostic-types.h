// Copyright (C) 2020  Matthew "strager" Glazar
// See end of file for extended copyright information.

#ifndef QUICK_LINT_JS_DIAG_DIAGNOSTIC_TYPES_H
#define QUICK_LINT_JS_DIAG_DIAGNOSTIC_TYPES_H

#include <iosfwd>
#include <quick-lint-js/fe/identifier.h>
#include <quick-lint-js/fe/language.h>
#include <quick-lint-js/fe/source-code-span.h>
#include <quick-lint-js/fe/token.h>
#include <quick-lint-js/i18n/translation.h>
#include <quick-lint-js/port/char8.h>

// QLJS_DIAG_TYPE should have the following signature:
//
// #define QLJS_DIAG_TYPE(error_name, error_code, severity, struct_body,
// format) ...
//
// * error_name: identifier
// * error_code: string literal
// * severity: diagnostic_severity value
// * struct_body: class member list, wrapped in { }
// * format: member function calls
//
// A class named *error_name* is created in the quick_lint_js namespace.
// *struct_body* is the body of the class.
//
// *format* should look like the following:
//
//    MESSAGE(QLJS_TRANSLATABLE("format string"), source_location)
//
// Within *format*:
//
// * MESSAGE's first argument must be QLJS_TRANSLATABLE(...)
// * MESSAGE's second argument must be a member variable of the *error_name*
//   class (i.e. listed in *struct_body*)
// * MESSAGE's second argument must have type *identifier* or *source_code_span*
//
// When removing a diagnostic from this list, add an entry to
// QLJS_X_RESERVED_DIAG_TYPES.
#define QLJS_X_DIAG_TYPES                                                       \
  QLJS_DIAG_TYPE(                                                               \
      diag_abstract_field_cannot_have_initializer, "E0295",                     \
      diagnostic_severity::error,                                               \
      {                                                                         \
        source_code_span equal;                                                 \
        source_code_span abstract_keyword;                                      \
      },                                                                        \
      MESSAGE(QLJS_TRANSLATABLE("abstract fields cannot have default values"),  \
              equal) MESSAGE(QLJS_TRANSLATABLE("field marked abstract here"),   \
                             abstract_keyword))                                 \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_abstract_methods_cannot_be_async, "E0298",                           \
      diagnostic_severity::error,                                               \
      {                                                                         \
        source_code_span async_keyword;                                         \
        source_code_span abstract_keyword;                                      \
      },                                                                        \
      MESSAGE(QLJS_TRANSLATABLE("abstract methods cannot be marked 'async'"),   \
              async_keyword))                                                   \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_abstract_methods_cannot_be_generators, "E0299",                      \
      diagnostic_severity::error,                                               \
      {                                                                         \
        source_code_span star;                                                  \
        source_code_span abstract_keyword;                                      \
      },                                                                        \
      MESSAGE(QLJS_TRANSLATABLE(                                                \
                  "abstract methods cannot be marked as a generator"),          \
              star))                                                            \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_abstract_property_not_allowed_in_interface, "E0297",                 \
      diagnostic_severity::error, { source_code_span abstract_keyword; },       \
      MESSAGE(QLJS_TRANSLATABLE(                                                \
                  "abstract properties are not allowed in interfaces"),         \
              abstract_keyword))                                                \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_abstract_property_not_allowed_in_non_abstract_class, "E0296",        \
      diagnostic_severity::error,                                               \
      {                                                                         \
        source_code_span abstract_keyword;                                      \
        source_code_span class_keyword;                                         \
      },                                                                        \
      MESSAGE(QLJS_TRANSLATABLE(                                                \
                  "abstract properties are only allowed in abstract classes"),  \
              abstract_keyword)                                                 \
          MESSAGE(QLJS_TRANSLATABLE("class is not marked abstract"),            \
                  class_keyword))                                               \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_abstract_methods_cannot_contain_bodies, "E0294",                     \
      diagnostic_severity::error, { source_code_span body_start; },             \
      MESSAGE(QLJS_TRANSLATABLE("abstract methods cannot contain a body"),      \
              body_start))                                                      \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_adjacent_jsx_without_parent, "E0189", diagnostic_severity::error,    \
      {                                                                         \
        source_code_span begin;                                                 \
        source_code_span begin_of_second_element;                               \
        source_code_span end;                                                   \
      },                                                                        \
      MESSAGE(QLJS_TRANSLATABLE(                                                \
                  "missing '<>' and '</>' to enclose multiple children"),       \
              begin) MESSAGE(QLJS_TRANSLATABLE("children end here"), end))      \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_arrow_parameter_with_type_annotation_requires_parentheses, "E0255",  \
      diagnostic_severity::error,                                               \
      {                                                                         \
        source_code_span parameter_and_annotation;                              \
        source_code_span type_colon;                                            \
      },                                                                        \
      MESSAGE(QLJS_TRANSLATABLE("missing parentheses around parameter"),        \
              parameter_and_annotation)                                         \
          MESSAGE(QLJS_TRANSLATABLE(                                            \
                      "TypeScript type annotation requires parentheses"),       \
                  type_colon))                                                  \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_typescript_question_in_type_expression_should_be_void, "E0348",      \
      diagnostic_severity::error, { source_code_span question; },               \
      MESSAGE(                                                                  \
          QLJS_TRANSLATABLE("invalid usage of ? as a prefix or suffix in "      \
                            "the a type expression, use '| void' instead"),     \
          question))                                                            \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_assignment_before_variable_declaration, "E0001",                     \
      diagnostic_severity::error,                                               \
      {                                                                         \
        identifier assignment;                                                  \
        identifier declaration;                                                 \
      },                                                                        \
      MESSAGE(QLJS_TRANSLATABLE("variable assigned before its declaration"),    \
              assignment)                                                       \
          MESSAGE(QLJS_TRANSLATABLE("variable declared here"), declaration))    \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_assignment_makes_condition_constant, "E0188",                        \
      diagnostic_severity::warning, { source_code_span assignment_operator; },  \
      MESSAGE(QLJS_TRANSLATABLE(                                                \
                  "'=' changes variables; to compare, use '===' instead"),      \
              assignment_operator))                                             \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_assignment_to_const_global_variable, "E0002",                        \
      diagnostic_severity::error, { identifier assignment; },                   \
      MESSAGE(QLJS_TRANSLATABLE("assignment to const global variable"),         \
              assignment))                                                      \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_assignment_to_const_variable, "E0003", diagnostic_severity::error,   \
      {                                                                         \
        identifier declaration;                                                 \
        identifier assignment;                                                  \
        variable_kind var_kind;                                                 \
      },                                                                        \
      MESSAGE(QLJS_TRANSLATABLE("assignment to const variable"), assignment)    \
          MESSAGE(QLJS_TRANSLATABLE("const variable declared here"),            \
                  declaration))                                                 \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_assignment_to_imported_variable, "E0185",                            \
      diagnostic_severity::error,                                               \
      {                                                                         \
        identifier declaration;                                                 \
        identifier assignment;                                                  \
        variable_kind var_kind;                                                 \
      },                                                                        \
      MESSAGE(QLJS_TRANSLATABLE("assignment to imported variable"),             \
              assignment)                                                       \
          MESSAGE(QLJS_TRANSLATABLE("imported variable declared here"),         \
                  declaration))                                                 \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_assignment_to_const_variable_before_its_declaration, "E0004",        \
      diagnostic_severity::error,                                               \
      {                                                                         \
        identifier declaration;                                                 \
        identifier assignment;                                                  \
        variable_kind var_kind;                                                 \
      },                                                                        \
      MESSAGE(QLJS_TRANSLATABLE(                                                \
                  "assignment to const variable before its declaration"),       \
              assignment)                                                       \
          MESSAGE(QLJS_TRANSLATABLE("const variable declared here"),            \
                  declaration))                                                 \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_assignment_to_undeclared_variable, "E0059",                          \
      diagnostic_severity::warning, { identifier assignment; },                 \
      MESSAGE(QLJS_TRANSLATABLE("assignment to undeclared variable"),           \
              assignment))                                                      \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_await_operator_outside_async, "E0162", diagnostic_severity::error,   \
      { source_code_span await_operator; },                                     \
      MESSAGE(QLJS_TRANSLATABLE("'await' is only allowed in async functions"),  \
              await_operator))                                                  \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_await_followed_by_arrow_function, "E0178",                           \
      diagnostic_severity::error, { source_code_span await_operator; },         \
      MESSAGE(QLJS_TRANSLATABLE("'await' cannot be followed by an arrow "       \
                                "function; use 'async' instead"),               \
              await_operator))                                                  \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_async_static_method, "E0269", diagnostic_severity::error,            \
      { source_code_span async_static; },                                       \
      MESSAGE(                                                                  \
          QLJS_TRANSLATABLE(                                                    \
              "'async static' is not allowed; write 'static async' instead"),   \
          async_static))                                                        \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_async_export_function, "E0326", diagnostic_severity::error,          \
      { source_code_span async_export; },                                       \
      MESSAGE(                                                                  \
          QLJS_TRANSLATABLE(                                                    \
              "'async export' is not allowed; write 'export async' instead"),   \
          async_export))                                                        \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_declare_class_fields_cannot_have_initializers, "E0335",              \
      diagnostic_severity::error, { source_code_span equal; },                  \
      MESSAGE(                                                                  \
          QLJS_TRANSLATABLE("'declare class' fields cannot be initalized"),     \
          equal))                                                               \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_declare_class_methods_cannot_be_async, "E0338",                      \
      diagnostic_severity::error, { source_code_span async_keyword; },          \
      MESSAGE(QLJS_TRANSLATABLE(                                                \
                  "'declare class' methods cannot be marked 'async'"),          \
              async_keyword))                                                   \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_declare_class_methods_cannot_be_generators, "E0337",                 \
      diagnostic_severity::error, { source_code_span star; },                   \
      MESSAGE(QLJS_TRANSLATABLE(                                                \
                  "'declare class' methods cannot be marked as a generator"),   \
              star))                                                            \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_declare_class_methods_cannot_contain_bodies, "E0333",                \
      diagnostic_severity::error, { source_code_span body_start; },             \
      MESSAGE(                                                                  \
          QLJS_TRANSLATABLE("'declare class' methods cannot contain a body"),   \
          body_start))                                                          \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_declare_abstract_class_not_allowed_in_javascript, "E0340",           \
      diagnostic_severity::error, { source_code_span declare_keyword; },        \
      MESSAGE(QLJS_TRANSLATABLE("TypeScript 'declare abstract class' is not "   \
                                "allowed in JavaScript"),                       \
              declare_keyword))                                                 \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_declare_class_not_allowed_in_javascript, "E0339",                    \
      diagnostic_severity::error, { source_code_span declare_keyword; },        \
      MESSAGE(QLJS_TRANSLATABLE(                                                \
                  "TypeScript 'declare class' is not allowed in JavaScript"),   \
              declare_keyword))                                                 \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_declare_function_cannot_be_async, "E0354",                           \
      diagnostic_severity::error, { source_code_span async_keyword; },          \
      MESSAGE(                                                                  \
          QLJS_TRANSLATABLE("'declare function' cannot be marked 'async'"),     \
          async_keyword))                                                       \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_declare_function_cannot_be_generator, "E0355",                       \
      diagnostic_severity::error, { source_code_span star; },                   \
      MESSAGE(QLJS_TRANSLATABLE(                                                \
                  "'declare function' cannot be marked as a generator"),        \
              star))                                                            \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_declare_function_cannot_have_body, "E0353",                          \
      diagnostic_severity::error,                                               \
      {                                                                         \
        source_code_span body_start;                                            \
        source_code_span declare_keyword;                                       \
      },                                                                        \
      MESSAGE(QLJS_TRANSLATABLE("'declare function' cannot have a body"),       \
              body_start)                                                       \
          MESSAGE(QLJS_TRANSLATABLE("'declare function' here"),                 \
                  declare_keyword))                                             \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_declare_function_not_allowed_in_javascript, "E0352",                 \
      diagnostic_severity::error, { source_code_span declare_keyword; },        \
      MESSAGE(QLJS_TRANSLATABLE("TypeScript 'declare function' is not "         \
                                "allowed in JavaScript"),                       \
              declare_keyword))                                                 \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_declare_keyword_is_not_allowed_inside_declare_namespace, "E0358",    \
      diagnostic_severity::error,                                               \
      {                                                                         \
        source_code_span declare_keyword;                                       \
        source_code_span declare_namespace_declare_keyword;                     \
      },                                                                        \
      MESSAGE(                                                                  \
          QLJS_TRANSLATABLE(                                                    \
              "'declare' should not be written inside a 'declare namespace'"),  \
          declare_keyword)                                                      \
          MESSAGE(                                                              \
              QLJS_TRANSLATABLE("containing 'declare namespace' starts here"),  \
              declare_namespace_declare_keyword))                               \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_declare_namespace_cannot_contain_statement, "E0357",                 \
      diagnostic_severity::error,                                               \
      {                                                                         \
        source_code_span first_statement_token;                                 \
        source_code_span declare_keyword;                                       \
      },                                                                        \
      MESSAGE(QLJS_TRANSLATABLE("'declare namespace' cannot contain "           \
                                "statements, only declarations"),               \
              first_statement_token)                                            \
          MESSAGE(QLJS_TRANSLATABLE("'declare' here"), declare_keyword))        \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_declare_namespace_cannot_export_default, "E0363",                    \
      diagnostic_severity::error,                                               \
      {                                                                         \
        source_code_span default_keyword;                                       \
        source_code_span declare_keyword;                                       \
      },                                                                        \
      MESSAGE(                                                                  \
          QLJS_TRANSLATABLE(                                                    \
              "cannot 'export default' from inside a 'declare namespace'"),     \
          default_keyword)                                                      \
          MESSAGE(QLJS_TRANSLATABLE("'declare namespace' starts here"),         \
                  declare_keyword))                                             \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_declare_namespace_cannot_import_module, "E0362",                     \
      diagnostic_severity::error,                                               \
      {                                                                         \
        /* importing_keyword is either 'import', 'from', or 'require'. */       \
        source_code_span importing_keyword;                                     \
        source_code_span declare_keyword;                                       \
      },                                                                        \
      MESSAGE(QLJS_TRANSLATABLE(                                                \
                  "cannot import a module from inside a 'declare namespace'"),  \
              importing_keyword)                                                \
          MESSAGE(QLJS_TRANSLATABLE("'declare namespace' starts here"),         \
                  declare_keyword))                                             \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_declare_var_cannot_have_initializer, "E0351",                        \
      diagnostic_severity::error,                                               \
      {                                                                         \
        source_code_span equal;                                                 \
        source_code_span declare_keyword;                                       \
        source_code_span declaring_token;                                       \
      },                                                                        \
      MESSAGE(QLJS_TRANSLATABLE("'declare {1}' cannot have initializer"),       \
              equal, declaring_token)                                           \
          MESSAGE(QLJS_TRANSLATABLE("'declare {1}' started here"),              \
                  declare_keyword, declaring_token))                            \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_declare_var_not_allowed_in_javascript, "E0350",                      \
      diagnostic_severity::error,                                               \
      {                                                                         \
        source_code_span declare_keyword;                                       \
        source_code_span declaring_token;                                       \
      },                                                                        \
      MESSAGE(QLJS_TRANSLATABLE("TypeScript 'declare {1}' is not "              \
                                "allowed in JavaScript"),                       \
              declare_keyword, declaring_token))                                \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_function_async_function, "E0327", diagnostic_severity::error,        \
      { source_code_span function_async; },                                     \
      MESSAGE(QLJS_TRANSLATABLE("'function async' is not allowed; write "       \
                                "'async function' instead"),                    \
              function_async))                                                  \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_big_int_literal_contains_decimal_point, "E0005",                     \
      diagnostic_severity::error, { source_code_span where; },                  \
      MESSAGE(QLJS_TRANSLATABLE("BigInt literal contains decimal point"),       \
              where))                                                           \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_big_int_literal_contains_exponent, "E0006",                          \
      diagnostic_severity::error, { source_code_span where; },                  \
      MESSAGE(QLJS_TRANSLATABLE("BigInt literal contains exponent"), where))    \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_c_style_for_loop_is_missing_third_component, "E0093",                \
      diagnostic_severity::error,                                               \
      {                                                                         \
        source_code_span expected_last_component;                               \
        source_code_span existing_semicolon;                                    \
      },                                                                        \
      MESSAGE(QLJS_TRANSLATABLE(                                                \
                  "C-style for loop is missing its third component"),           \
              expected_last_component))                                         \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_cannot_assign_to_loop_variable_in_for_of_or_in_loop, "E0173",        \
      diagnostic_severity::error, { source_code_span equal_token; },            \
      MESSAGE(QLJS_TRANSLATABLE(                                                \
                  "cannot assign to loop variable in for of/in loop"),          \
              equal_token))                                                     \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_cannot_access_private_identifier_outside_class, "E0208",             \
      diagnostic_severity::error, { identifier private_identifier; },           \
      MESSAGE(                                                                  \
          QLJS_TRANSLATABLE("cannot access private identifier outside class"),  \
          private_identifier))                                                  \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_cannot_assign_to_variable_named_async_in_for_of_loop, "E0082",       \
      diagnostic_severity::error, { identifier async_identifier; },             \
      MESSAGE(                                                                  \
          QLJS_TRANSLATABLE(                                                    \
              "assigning to 'async' in a for-of loop requires parentheses"),    \
          async_identifier))                                                    \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_cannot_declare_await_in_async_function, "E0069",                     \
      diagnostic_severity::error, { identifier name; },                         \
      MESSAGE(                                                                  \
          QLJS_TRANSLATABLE("cannot declare 'await' inside async function"),    \
          name))                                                                \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_cannot_declare_class_named_let, "E0007",                             \
      diagnostic_severity::error, { source_code_span name; },                   \
      MESSAGE(QLJS_TRANSLATABLE("classes cannot be named 'let'"), name))        \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_cannot_declare_variable_named_let_with_let, "E0008",                 \
      diagnostic_severity::error, { source_code_span name; },                   \
      MESSAGE(QLJS_TRANSLATABLE(                                                \
                  "let statement cannot declare variables named 'let'"),        \
              name))                                                            \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_cannot_declare_variable_with_keyword_name, "E0124",                  \
      diagnostic_severity::error, { source_code_span keyword; },                \
      MESSAGE(                                                                  \
          QLJS_TRANSLATABLE("cannot declare variable named keyword '{0}'"),     \
          keyword))                                                             \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_cannot_declare_yield_in_generator_function, "E0071",                 \
      diagnostic_severity::error, { identifier name; },                         \
      MESSAGE(QLJS_TRANSLATABLE(                                                \
                  "cannot declare 'yield' inside generator function"),          \
              name))                                                            \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_cannot_export_default_variable, "E0076",                             \
      diagnostic_severity::error, { source_code_span declaring_token; },        \
      MESSAGE(QLJS_TRANSLATABLE(                                                \
                  "cannot declare and export variable with 'export default'"),  \
              declaring_token))                                                 \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_cannot_export_let, "E0009", diagnostic_severity::error,              \
      { source_code_span export_name; },                                        \
      MESSAGE(QLJS_TRANSLATABLE("cannot export variable named 'let'"),          \
              export_name))                                                     \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_cannot_export_variable_named_keyword, "E0144",                       \
      diagnostic_severity::error, { identifier export_name; },                  \
      MESSAGE(QLJS_TRANSLATABLE("cannot export variable named keyword '{0}'"),  \
              export_name))                                                     \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_cannot_import_let, "E0010", diagnostic_severity::error,              \
      { source_code_span import_name; },                                        \
      MESSAGE(QLJS_TRANSLATABLE("cannot import 'let'"), import_name))           \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_cannot_import_variable_named_keyword, "E0145",                       \
      diagnostic_severity::error, { identifier import_name; },                  \
      MESSAGE(QLJS_TRANSLATABLE("cannot import variable named keyword '{0}'"),  \
              import_name))                                                     \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_cannot_import_from_unquoted_module, "E0235",                         \
      diagnostic_severity::error, { identifier import_name; },                  \
      MESSAGE(QLJS_TRANSLATABLE("missing quotes around module name '{0}'"),     \
              import_name))                                                     \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_cannot_refer_to_private_variable_without_object, "E0155",            \
      diagnostic_severity::error, { identifier private_identifier; },           \
      MESSAGE(QLJS_TRANSLATABLE("cannot reference private variables without "   \
                                "object; use 'this.'"),                         \
              private_identifier))                                              \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_cannot_update_variable_during_declaration, "E0136",                  \
      diagnostic_severity::error,                                               \
      {                                                                         \
        source_code_span declaring_token;                                       \
        source_code_span updating_operator;                                     \
      },                                                                        \
      MESSAGE(QLJS_TRANSLATABLE(                                                \
                  "cannot update variable with '{0}' while declaring it"),      \
              updating_operator)                                                \
          MESSAGE(QLJS_TRANSLATABLE(                                            \
                      "remove '{0}' to update an existing variable"),           \
                  declaring_token))                                             \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_catch_without_try, "E0117", diagnostic_severity::error,              \
      { source_code_span catch_token; },                                        \
      MESSAGE(QLJS_TRANSLATABLE("unexpected 'catch' without 'try'"),            \
              catch_token))                                                     \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_class_statement_not_allowed_in_body, "E0149",                        \
      diagnostic_severity::error,                                               \
      {                                                                         \
        statement_kind kind_of_statement;                                       \
        source_code_span expected_body;                                         \
        source_code_span class_keyword;                                         \
      },                                                                        \
      MESSAGE(QLJS_TRANSLATABLE("missing body for {1:headlinese}"),             \
              expected_body, kind_of_statement)                                 \
          MESSAGE(QLJS_TRANSLATABLE("a class statement is not allowed as the "  \
                                    "body of {1:singular}"),                    \
                  class_keyword, kind_of_statement))                            \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_character_disallowed_in_identifiers, "E0011",                        \
      diagnostic_severity::error, { source_code_span character; },              \
      MESSAGE(QLJS_TRANSLATABLE("character is not allowed in identifiers"),     \
              character))                                                       \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_comma_not_allowed_after_spread_parameter, "E0070",                   \
      diagnostic_severity::error,                                               \
      {                                                                         \
        source_code_span comma;                                                 \
        source_code_span spread;                                                \
      },                                                                        \
      MESSAGE(                                                                  \
          QLJS_TRANSLATABLE("commas are not allowed after spread parameter"),   \
          comma))                                                               \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_comma_not_allowed_before_first_generic_parameter, "E0262",           \
      diagnostic_severity::error, { source_code_span unexpected_comma; },       \
      MESSAGE(                                                                  \
          QLJS_TRANSLATABLE(                                                    \
              "leading commas are not allowed in generic parameter lists"),     \
          unexpected_comma))                                                    \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_comma_not_allowed_between_class_methods, "E0209",                    \
      diagnostic_severity::error, { source_code_span unexpected_comma; },       \
      MESSAGE(                                                                  \
          QLJS_TRANSLATABLE("commas are not allowed between class methods"),    \
          unexpected_comma))                                                    \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_config_json_syntax_error, "E0164", diagnostic_severity::error,       \
      { source_code_span where; },                                              \
      MESSAGE(QLJS_TRANSLATABLE("JSON syntax error"), where))                   \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_config_global_groups_group_type_mismatch, "E0170",                   \
      diagnostic_severity::error, { source_code_span group; },                  \
      MESSAGE(QLJS_TRANSLATABLE("\"global-groups\" entries must be strings"),   \
              group))                                                           \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_config_global_groups_type_mismatch, "E0169",                         \
      diagnostic_severity::error, { source_code_span value; },                  \
      MESSAGE(QLJS_TRANSLATABLE(                                                \
                  "\"global-groups\" must be a boolean or an array"),           \
              value))                                                           \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_config_globals_descriptor_type_mismatch, "E0171",                    \
      diagnostic_severity::error, { source_code_span descriptor; },             \
      MESSAGE(QLJS_TRANSLATABLE(                                                \
                  "\"globals\" descriptor must be a boolean or an object"),     \
              descriptor))                                                      \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_config_globals_descriptor_shadowable_type_mismatch, "E0166",         \
      diagnostic_severity::error, { source_code_span value; },                  \
      MESSAGE(QLJS_TRANSLATABLE("\"globals\" descriptor \"shadowable\" "        \
                                "property must be a boolean"),                  \
              value))                                                           \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_config_globals_descriptor_writable_type_mismatch, "E0167",           \
      diagnostic_severity::error, { source_code_span value; },                  \
      MESSAGE(                                                                  \
          QLJS_TRANSLATABLE("\"globals\" descriptor \"writable\" property "     \
                            "must be a boolean"),                               \
          value))                                                               \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_config_globals_type_mismatch, "E0168", diagnostic_severity::error,   \
      { source_code_span value; },                                              \
      MESSAGE(QLJS_TRANSLATABLE("\"globals\" must be an object"), value))       \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_depth_limit_exceeded, "E0203", diagnostic_severity::error,           \
      { source_code_span token; },                                              \
      MESSAGE(QLJS_TRANSLATABLE("depth limit exceeded"), token))                \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_dot_not_allowed_after_generic_arguments_in_type, "E0259",            \
      diagnostic_severity::error,                                               \
      {                                                                         \
        source_code_span dot;                                                   \
        source_code_span property_name;                                         \
      },                                                                        \
      MESSAGE(QLJS_TRANSLATABLE("'.' is not allowed after generic arguments; "  \
                                "write [\"{1}\"] instead"),                     \
              dot, property_name))                                              \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_dot_dot_is_not_an_operator, "E0053", diagnostic_severity::error,     \
      { source_code_span dots; },                                               \
      MESSAGE(QLJS_TRANSLATABLE("missing property name between '.' and '.'"),   \
              dots))                                                            \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_duplicated_cases_in_switch_statement, "E0347",                       \
      diagnostic_severity::warning,                                             \
      {                                                                         \
        source_code_span first_switch_case;                                     \
        source_code_span duplicated_switch_case;                                \
      },                                                                        \
      MESSAGE(QLJS_TRANSLATABLE("duplicated case clause in switch statement"),  \
              duplicated_switch_case)                                           \
          MESSAGE(QLJS_TRANSLATABLE("this case will run instead"),              \
                  first_switch_case))                                           \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_else_has_no_if, "E0065", diagnostic_severity::error,                 \
      { source_code_span else_token; },                                         \
      MESSAGE(QLJS_TRANSLATABLE("'else' has no corresponding 'if'"),            \
              else_token))                                                      \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_equals_does_not_distribute_over_or, "E0190",                         \
      diagnostic_severity::warning,                                             \
      {                                                                         \
        source_code_span or_operator;                                           \
        source_code_span equals_operator;                                       \
      },                                                                        \
      MESSAGE(QLJS_TRANSLATABLE("missing comparison; '{1}' does not extend "    \
                                "to the right side of '{0}'"),                  \
              or_operator, equals_operator)                                     \
          MESSAGE(QLJS_TRANSLATABLE("'{0}' found here"), equals_operator))      \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_escaped_character_disallowed_in_identifiers, "E0012",                \
      diagnostic_severity::error, { source_code_span escape_sequence; },        \
      MESSAGE(QLJS_TRANSLATABLE(                                                \
                  "escaped character is not allowed in identifiers"),           \
              escape_sequence))                                                 \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_escaped_code_point_in_identifier_out_of_range, "E0013",              \
      diagnostic_severity::error, { source_code_span escape_sequence; },        \
      MESSAGE(QLJS_TRANSLATABLE("code point out of range"), escape_sequence))   \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_escaped_code_point_in_unicode_out_of_range, "E0207",                 \
      diagnostic_severity::error, { source_code_span escape_sequence; },        \
      MESSAGE(QLJS_TRANSLATABLE("code point in Unicode escape sequence must "   \
                                "not be greater than U+10FFFF"),                \
              escape_sequence))                                                 \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_escaped_hyphen_not_allowed_in_jsx_tag, "E0019",                      \
      diagnostic_severity::error, { source_code_span escape_sequence; },        \
      MESSAGE(                                                                  \
          QLJS_TRANSLATABLE(                                                    \
              "escaping '-' is not allowed in tag names; write '-' instead"),   \
          escape_sequence))                                                     \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_extra_comma_not_allowed_between_arguments, "E0068",                  \
      diagnostic_severity::error, { source_code_span comma; },                  \
      MESSAGE(QLJS_TRANSLATABLE(                                                \
                  "extra ',' is not allowed between function call arguments"),  \
              comma))                                                           \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_extra_comma_not_allowed_between_enum_members, "E0248",               \
      diagnostic_severity::error, { source_code_span comma; },                  \
      MESSAGE(                                                                  \
          QLJS_TRANSLATABLE("extra ',' is not allowed between enum members"),   \
          comma))                                                               \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_misleading_comma_operator_in_index_operation, "E0450",               \
      diagnostic_severity::warning,                                             \
      {                                                                         \
        source_code_span comma;                                                 \
        source_code_span left_square;                                           \
      },                                                                        \
      MESSAGE(QLJS_TRANSLATABLE("misleading use of ',' operator in index"),     \
              comma)                                                            \
          MESSAGE(QLJS_TRANSLATABLE("index starts here"), left_square))         \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_misleading_comma_operator_in_conditional_statement, "E0451",         \
      diagnostic_severity::warning, { source_code_span comma; },                \
      MESSAGE(QLJS_TRANSLATABLE(                                                \
                  "misleading use of ',' operator in conditional statement"),   \
              comma))                                                           \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_empty_paren_after_control_statement, "E0452",                        \
      diagnostic_severity::error,                                               \
      {                                                                         \
        source_code_span token;                                                 \
        source_code_span expected_expression;                                   \
      },                                                                        \
      MESSAGE(QLJS_TRANSLATABLE("expected expression after '('"),               \
              expected_expression)                                              \
          MESSAGE(QLJS_TRANSLATABLE("'{1}' statement starts here"), token,      \
                  token))                                                       \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_expected_as_before_imported_namespace_alias, "E0126",                \
      diagnostic_severity::error,                                               \
      {                                                                         \
        source_code_span star_through_alias_token;                              \
        source_code_span alias;                                                 \
        source_code_span star_token;                                            \
      },                                                                        \
      MESSAGE(QLJS_TRANSLATABLE("expected 'as' between '{1}' and '{2}'"),       \
              star_through_alias_token, star_token, alias))                     \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_expected_comma_to_separate_object_literal_entries, "E0131",          \
      diagnostic_severity::error, { source_code_span unexpected_token; },       \
      MESSAGE(                                                                  \
          QLJS_TRANSLATABLE("expected ',' between object literal entries"),     \
          unexpected_token))                                                    \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_expected_expression_before_newline, "E0014",                         \
      diagnostic_severity::error, { source_code_span where; },                  \
      MESSAGE(QLJS_TRANSLATABLE("expected expression before newline"), where))  \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_expected_expression_for_switch_case, "E0140",                        \
      diagnostic_severity::error, { source_code_span case_token; },             \
      MESSAGE(QLJS_TRANSLATABLE("expected expression after 'case'"),            \
              case_token))                                                      \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_expected_expression_before_semicolon, "E0015",                       \
      diagnostic_severity::error, { source_code_span where; },                  \
      MESSAGE(QLJS_TRANSLATABLE("expected expression before semicolon"),        \
              where))                                                           \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_expected_from_and_module_specifier, "E0129",                         \
      diagnostic_severity::error, { source_code_span where; },                  \
      MESSAGE(QLJS_TRANSLATABLE("expected 'from \"name_of_module.mjs\"'"),      \
              where))                                                           \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_expected_from_before_module_specifier, "E0128",                      \
      diagnostic_severity::error, { source_code_span module_specifier; },       \
      MESSAGE(QLJS_TRANSLATABLE("expected 'from' before module specifier"),     \
              module_specifier))                                                \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_expected_hex_digits_in_unicode_escape, "E0016",                      \
      diagnostic_severity::error, { source_code_span escape_sequence; },        \
      MESSAGE(QLJS_TRANSLATABLE(                                                \
                  "expected hexadecimal digits in Unicode escape sequence"),    \
              escape_sequence))                                                 \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_expected_left_curly, "E0107", diagnostic_severity::error,            \
      { source_code_span expected_left_curly; },                                \
      MESSAGE(QLJS_TRANSLATABLE("expected '{{'"), expected_left_curly))         \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_expected_right_paren_for_function_call, "E0141",                     \
      diagnostic_severity::error,                                               \
      {                                                                         \
        source_code_span expected_right_paren;                                  \
        source_code_span left_paren;                                            \
      },                                                                        \
      MESSAGE(QLJS_TRANSLATABLE("expected ')' to close function call"),         \
              expected_right_paren)                                             \
          MESSAGE(QLJS_TRANSLATABLE("function call started here"),              \
                  left_paren))                                                  \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_expected_parentheses_around_do_while_condition, "E0084",             \
      diagnostic_severity::error, { source_code_span condition; },              \
      MESSAGE(QLJS_TRANSLATABLE(                                                \
                  "do-while loop needs parentheses around condition"),          \
              condition))                                                       \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_expected_parenthesis_around_do_while_condition, "E0085",             \
      diagnostic_severity::error,                                               \
      {                                                                         \
        source_code_span where;                                                 \
        char8 token;                                                            \
      },                                                                        \
      MESSAGE(QLJS_TRANSLATABLE(                                                \
                  "do-while loop is missing '{1}' around condition"),           \
              where, token))                                                    \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_expected_parentheses_around_if_condition, "E0017",                   \
      diagnostic_severity::error, { source_code_span condition; },              \
      MESSAGE(QLJS_TRANSLATABLE(                                                \
                  "if statement needs parentheses around condition"),           \
              condition))                                                       \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_expected_parenthesis_around_if_condition, "E0018",                   \
      diagnostic_severity::error,                                               \
      {                                                                         \
        source_code_span where;                                                 \
        char8 token;                                                            \
      },                                                                        \
      MESSAGE(                                                                  \
          QLJS_TRANSLATABLE("if statement is missing '{1}' around condition"),  \
          where, token))                                                        \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_expected_parentheses_around_switch_condition, "E0091",               \
      diagnostic_severity::error, { source_code_span condition; },              \
      MESSAGE(QLJS_TRANSLATABLE(                                                \
                  "switch statement needs parentheses around condition"),       \
              condition))                                                       \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_expected_parenthesis_around_switch_condition, "E0092",               \
      diagnostic_severity::error,                                               \
      {                                                                         \
        source_code_span where;                                                 \
        char8 token;                                                            \
      },                                                                        \
      MESSAGE(QLJS_TRANSLATABLE(                                                \
                  "switch statement is missing '{1}' around condition"),        \
              where, token))                                                    \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_expected_parentheses_around_while_condition, "E0087",                \
      diagnostic_severity::error, { source_code_span condition; },              \
      MESSAGE(                                                                  \
          QLJS_TRANSLATABLE("while loop needs parentheses around condition"),   \
          condition))                                                           \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_expected_parenthesis_around_while_condition, "E0088",                \
      diagnostic_severity::error,                                               \
      {                                                                         \
        source_code_span where;                                                 \
        char8 token;                                                            \
      },                                                                        \
      MESSAGE(                                                                  \
          QLJS_TRANSLATABLE("while loop is missing '{1}' around condition"),    \
          where, token))                                                        \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_expected_parentheses_around_with_expression, "E0089",                \
      diagnostic_severity::error, { source_code_span expression; },             \
      MESSAGE(QLJS_TRANSLATABLE(                                                \
                  "with statement needs parentheses around expression"),        \
              expression))                                                      \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_expected_parenthesis_around_with_expression, "E0090",                \
      diagnostic_severity::error,                                               \
      {                                                                         \
        source_code_span where;                                                 \
        char8 token;                                                            \
      },                                                                        \
      MESSAGE(QLJS_TRANSLATABLE(                                                \
                  "with statement is missing '{1}' around expression"),         \
              where, token))                                                    \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_expected_variable_name_for_catch, "E0135",                           \
      diagnostic_severity::error, { source_code_span unexpected_token; },       \
      MESSAGE(QLJS_TRANSLATABLE("expected variable name for 'catch'"),          \
              unexpected_token))                                                \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_expected_variable_name_for_import_as, "E0175",                       \
      diagnostic_severity::error, { source_code_span unexpected_token; },       \
      MESSAGE(QLJS_TRANSLATABLE("expected variable name for 'import'-'as'"),    \
              unexpected_token))                                                \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_exporting_requires_default, "E0067", diagnostic_severity::error,     \
      { source_code_span expression; },                                         \
      MESSAGE(QLJS_TRANSLATABLE("exporting requires 'default'"), expression))   \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_exporting_requires_curlies, "E0066", diagnostic_severity::error,     \
      { source_code_span names; },                                              \
      MESSAGE(QLJS_TRANSLATABLE("exporting requires '{{' and '}'"), names))     \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_exporting_string_name_only_allowed_for_export_from, "E0153",         \
      diagnostic_severity::error, { source_code_span export_name; },            \
      MESSAGE(QLJS_TRANSLATABLE(                                                \
                  "forwarding exports are only allowed in export-from"),        \
              export_name))                                                     \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_finally_without_try, "E0118", diagnostic_severity::error,            \
      { source_code_span finally_token; },                                      \
      MESSAGE(QLJS_TRANSLATABLE("unexpected 'finally' without 'try'"),          \
              finally_token))                                                   \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_function_statement_not_allowed_in_body, "E0148",                     \
      diagnostic_severity::error,                                               \
      {                                                                         \
        statement_kind kind_of_statement;                                       \
        source_code_span expected_body;                                         \
        source_code_span function_keywords;                                     \
      },                                                                        \
      MESSAGE(QLJS_TRANSLATABLE("missing body for {1:headlinese}"),             \
              expected_body, kind_of_statement)                                 \
          MESSAGE(                                                              \
              QLJS_TRANSLATABLE("a function statement is not allowed as the "   \
                                "body of {1:singular}"),                        \
              function_keywords, kind_of_statement))                            \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_generator_function_star_belongs_after_keyword_function, "E0204",     \
      diagnostic_severity::error, { source_code_span star; },                   \
      MESSAGE(QLJS_TRANSLATABLE(                                                \
                  "generator function '*' belongs after keyword function"),     \
              star))                                                            \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_generator_function_star_belongs_before_name, "E0133",                \
      diagnostic_severity::error,                                               \
      {                                                                         \
        source_code_span function_name;                                         \
        source_code_span star;                                                  \
      },                                                                        \
      MESSAGE(QLJS_TRANSLATABLE(                                                \
                  "generator function '*' belongs before function name"),       \
              star))                                                            \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_multiple_commas_in_generic_parameter_list, "E0263",                  \
      diagnostic_severity::error, { source_code_span unexpected_comma; },       \
      MESSAGE(QLJS_TRANSLATABLE("only one comma is allowed between or after "   \
                                "generic parameters"),                          \
              unexpected_comma))                                                \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_in_disallowed_in_c_style_for_loop, "E0108",                          \
      diagnostic_severity::error, { source_code_span in_token; },               \
      MESSAGE(QLJS_TRANSLATABLE(                                                \
                  "'in' disallowed in C-style for loop initializer"),           \
              in_token))                                                        \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_indexing_requires_expression, "E0075", diagnostic_severity::error,   \
      { source_code_span squares; },                                            \
      MESSAGE(QLJS_TRANSLATABLE("indexing requires an expression"), squares))   \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_invalid_expression_left_of_assignment, "E0020",                      \
      diagnostic_severity::error, { source_code_span where; },                  \
      MESSAGE(QLJS_TRANSLATABLE("invalid expression left of assignment"),       \
              where))                                                           \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_invalid_hex_escape_sequence, "E0060", diagnostic_severity::error,    \
      { source_code_span escape_sequence; },                                    \
      MESSAGE(QLJS_TRANSLATABLE("invalid hex escape sequence: {0}"),            \
              escape_sequence))                                                 \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_invalid_lone_literal_in_object_literal, "E0021",                     \
      diagnostic_severity::error, { source_code_span where; },                  \
      MESSAGE(QLJS_TRANSLATABLE("invalid lone literal in object literal"),      \
              where))                                                           \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_invalid_parameter, "E0151", diagnostic_severity::error,              \
      { source_code_span parameter; },                                          \
      MESSAGE(QLJS_TRANSLATABLE("invalid function parameter"), parameter))      \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_invalid_quotes_around_string_literal, "E0197",                       \
      diagnostic_severity::error,                                               \
      {                                                                         \
        source_code_span opening_quote;                                         \
        char8 suggested_quote;                                                  \
      },                                                                        \
      MESSAGE(QLJS_TRANSLATABLE(                                                \
                  "'{0}' is not allowed for strings; use {1} instead"),         \
              opening_quote, suggested_quote))                                  \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_invalid_rhs_for_dot_operator, "E0074", diagnostic_severity::error,   \
      { source_code_span dot; },                                                \
      MESSAGE(QLJS_TRANSLATABLE(                                                \
                  "'.' operator needs a key name; use + to concatenate "        \
                  "strings; use [] to access with a dynamic key"),              \
              dot))                                                             \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_invalid_utf_8_sequence, "E0022", diagnostic_severity::error,         \
      { source_code_span sequence; },                                           \
      MESSAGE(QLJS_TRANSLATABLE("invalid UTF-8 sequence"), sequence))           \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_jsx_attribute_has_wrong_capitalization, "E0192",                     \
      diagnostic_severity::error,                                               \
      {                                                                         \
        identifier attribute_name;                                              \
        string8_view expected_attribute_name;                                   \
      },                                                                        \
      MESSAGE(QLJS_TRANSLATABLE(                                                \
                  "attribute has wrong capitalization; write '{1}' instead"),   \
              attribute_name, expected_attribute_name))                         \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_jsx_attribute_renamed_by_react, "E0193",                             \
      diagnostic_severity::error,                                               \
      {                                                                         \
        identifier attribute_name;                                              \
        string8_view react_attribute_name;                                      \
      },                                                                        \
      MESSAGE(QLJS_TRANSLATABLE(                                                \
                  "misspelled React attribute; write '{1}' instead"),           \
              attribute_name, react_attribute_name))                            \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_jsx_event_attribute_should_be_camel_case, "E0191",                   \
      diagnostic_severity::error,                                               \
      {                                                                         \
        identifier attribute_name;                                              \
        string8_view expected_attribute_name;                                   \
      },                                                                        \
      MESSAGE(QLJS_TRANSLATABLE("event attributes must be camelCase: '{1}'"),   \
              attribute_name, expected_attribute_name))                         \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_jsx_not_allowed_in_javascript, "E0177", diagnostic_severity::error,  \
      { source_code_span jsx_start; },                                          \
      MESSAGE(QLJS_TRANSLATABLE(                                                \
                  "React/JSX is not allowed in vanilla JavaScript code"),       \
              jsx_start))                                                       \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_jsx_not_allowed_in_typescript, "E0306", diagnostic_severity::error,  \
      { source_code_span jsx_start; },                                          \
      MESSAGE(                                                                  \
          QLJS_TRANSLATABLE("React/JSX is not allowed in TypeScript code"),     \
          jsx_start))                                                           \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_keywords_cannot_contain_escape_sequences, "E0023",                   \
      diagnostic_severity::error, { source_code_span escape_sequence; },        \
      MESSAGE(QLJS_TRANSLATABLE("keywords cannot contain escape sequences"),    \
              escape_sequence))                                                 \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_label_named_await_not_allowed_in_async_function, "E0206",            \
      diagnostic_severity::error,                                               \
      {                                                                         \
        source_code_span await;                                                 \
        source_code_span colon;                                                 \
      },                                                                        \
      MESSAGE(QLJS_TRANSLATABLE(                                                \
                  "label named 'await' not allowed in async function"),         \
              await))                                                           \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_legacy_octal_literal_may_not_be_big_int, "E0032",                    \
      diagnostic_severity::error, { source_code_span characters; },             \
      MESSAGE(QLJS_TRANSLATABLE("legacy octal literal may not be BigInt"),      \
              characters))                                                      \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_legacy_octal_literal_may_not_contain_underscores, "E0152",           \
      diagnostic_severity::error, { source_code_span underscores; },            \
      MESSAGE(QLJS_TRANSLATABLE(                                                \
                  "legacy octal literals may not contain underscores"),         \
              underscores))                                                     \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_let_with_no_bindings, "E0024", diagnostic_severity::error,           \
      { source_code_span where; },                                              \
      MESSAGE(QLJS_TRANSLATABLE("{0} with no bindings"), where))                \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_lexical_declaration_not_allowed_in_body, "E0150",                    \
      diagnostic_severity::error,                                               \
      {                                                                         \
        statement_kind kind_of_statement;                                       \
        source_code_span expected_body;                                         \
        source_code_span declaring_keyword;                                     \
      },                                                                        \
      MESSAGE(QLJS_TRANSLATABLE("missing body for {1:headlinese}"),             \
              expected_body, kind_of_statement)                                 \
          MESSAGE(                                                              \
              QLJS_TRANSLATABLE("a lexical declaration is not allowed as the "  \
                                "body of {1:singular}"),                        \
              declaring_keyword, kind_of_statement))                            \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_functions_or_methods_should_not_have_arrow_operator, "E0174",        \
      diagnostic_severity::error, { source_code_span arrow_operator; },         \
      MESSAGE(QLJS_TRANSLATABLE("functions/methods should not have '=>'"),      \
              arrow_operator))                                                  \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_methods_should_not_use_function_keyword, "E0072",                    \
      diagnostic_severity::error, { source_code_span function_token; },         \
      MESSAGE(                                                                  \
          QLJS_TRANSLATABLE("methods should not use the 'function' keyword"),   \
          function_token))                                                      \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_mismatched_jsx_tags, "E0187", diagnostic_severity::error,            \
      {                                                                         \
        source_code_span opening_tag_name;                                      \
        source_code_span closing_tag_name;                                      \
        string8_view opening_tag_name_pretty;                                   \
      },                                                                        \
      MESSAGE(QLJS_TRANSLATABLE("mismatched JSX tags; expected '</{1}>'"),      \
              closing_tag_name, opening_tag_name_pretty)                        \
          MESSAGE(QLJS_TRANSLATABLE("opening '<{1}>' tag here"),                \
                  opening_tag_name, opening_tag_name_pretty))                   \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_missing_array_close, "E0157", diagnostic_severity::error,            \
      {                                                                         \
        source_code_span left_square;                                           \
        source_code_span expected_right_square;                                 \
      },                                                                        \
      MESSAGE(QLJS_TRANSLATABLE("missing end of array; expected ']'"),          \
              expected_right_square)                                            \
          MESSAGE(QLJS_TRANSLATABLE("array started here"), left_square))        \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_missing_arrow_operator_in_arrow_function, "E0176",                   \
      diagnostic_severity::error, { source_code_span where; },                  \
      MESSAGE(QLJS_TRANSLATABLE("missing arrow operator for arrow function"),   \
              where))                                                           \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_missing_arrow_function_parameter_list, "E0105",                      \
      diagnostic_severity::error, { source_code_span arrow; },                  \
      MESSAGE(QLJS_TRANSLATABLE("missing parameters for arrow function"),       \
              arrow))                                                           \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_missing_body_for_catch_clause, "E0119", diagnostic_severity::error,  \
      { source_code_span catch_token; },                                        \
      MESSAGE(QLJS_TRANSLATABLE("missing body for catch clause"),               \
              catch_token))                                                     \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_missing_body_for_class, "E0111", diagnostic_severity::error,         \
      { source_code_span class_keyword_and_name_and_heritage; },                \
      MESSAGE(QLJS_TRANSLATABLE("missing body for class"),                      \
              class_keyword_and_name_and_heritage))                             \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_missing_body_for_do_while_statement, "E0101",                        \
      diagnostic_severity::error, { source_code_span do_token; },               \
      MESSAGE(QLJS_TRANSLATABLE("missing body for do-while loop"), do_token))   \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_missing_body_for_finally_clause, "E0121",                            \
      diagnostic_severity::error, { source_code_span finally_token; },          \
      MESSAGE(QLJS_TRANSLATABLE("missing body for finally clause"),             \
              finally_token))                                                   \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_missing_body_for_for_statement, "E0094",                             \
      diagnostic_severity::error, { source_code_span for_and_header; },         \
      MESSAGE(QLJS_TRANSLATABLE("missing body for 'for' loop"),                 \
              for_and_header))                                                  \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_missing_body_for_if_statement, "E0064", diagnostic_severity::error,  \
      { source_code_span expected_body; },                                      \
      MESSAGE(QLJS_TRANSLATABLE("missing body for 'if' statement"),             \
              expected_body))                                                   \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_missing_body_for_switch_statement, "E0106",                          \
      diagnostic_severity::error, { source_code_span switch_and_condition; },   \
      MESSAGE(QLJS_TRANSLATABLE("missing body for 'switch' statement"),         \
              switch_and_condition))                                            \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_missing_body_for_try_statement, "E0120",                             \
      diagnostic_severity::error, { source_code_span try_token; },              \
      MESSAGE(QLJS_TRANSLATABLE("missing body for try statement"), try_token))  \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_missing_body_for_typescript_interface, "E0245",                      \
      diagnostic_severity::error,                                               \
      { source_code_span interface_keyword_and_name_and_heritage; },            \
      MESSAGE(QLJS_TRANSLATABLE("missing body for TypeScript interface"),       \
              interface_keyword_and_name_and_heritage))                         \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_missing_body_for_typescript_namespace, "E0356",                      \
      diagnostic_severity::error, { source_code_span expected_body; },          \
      MESSAGE(QLJS_TRANSLATABLE("missing body for TypeScript namespace"),       \
              expected_body))                                                   \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_missing_body_for_while_statement, "E0104",                           \
      diagnostic_severity::error, { source_code_span while_and_condition; },    \
      MESSAGE(QLJS_TRANSLATABLE("missing body for while loop"),                 \
              while_and_condition))                                             \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_missing_catch_or_finally_for_try_statement, "E0122",                 \
      diagnostic_severity::error,                                               \
      {                                                                         \
        source_code_span expected_catch_or_finally;                             \
        source_code_span try_token;                                             \
      },                                                                        \
      MESSAGE(QLJS_TRANSLATABLE(                                                \
                  "missing catch or finally clause for try statement"),         \
              expected_catch_or_finally)                                        \
          MESSAGE(QLJS_TRANSLATABLE("try statement starts here"), try_token))   \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_missing_catch_variable_between_parentheses, "E0130",                 \
      diagnostic_severity::error,                                               \
      {                                                                         \
        source_code_span left_paren_to_right_paren;                             \
        source_code_span left_paren;                                            \
        source_code_span right_paren;                                           \
      },                                                                        \
      MESSAGE(QLJS_TRANSLATABLE(                                                \
                  "missing catch variable name between parentheses"),           \
              left_paren_to_right_paren))                                       \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_missing_comma_between_object_literal_entries, "E0025",               \
      diagnostic_severity::error, { source_code_span where; },                  \
      MESSAGE(                                                                  \
          QLJS_TRANSLATABLE("missing comma between object literal entries"),    \
          where))                                                               \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_missing_comma_between_generic_parameters, "E0265",                   \
      diagnostic_severity::error, { source_code_span expected_comma; },         \
      MESSAGE(QLJS_TRANSLATABLE("missing comma between generic parameters"),    \
              expected_comma))                                                  \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_missing_comma_between_variable_declarations, "E0132",                \
      diagnostic_severity::error, { source_code_span expected_comma; },         \
      MESSAGE(QLJS_TRANSLATABLE("missing ',' between variable declarations"),   \
              expected_comma))                                                  \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_missing_colon_in_conditional_expression, "E0146",                    \
      diagnostic_severity::error,                                               \
      {                                                                         \
        source_code_span expected_colon;                                        \
        source_code_span question;                                              \
      },                                                                        \
      MESSAGE(QLJS_TRANSLATABLE("missing ':' in conditional expression"),       \
              expected_colon)                                                   \
          MESSAGE(QLJS_TRANSLATABLE("'?' creates a conditional expression"),    \
                  question))                                                    \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_missing_condition_for_if_statement, "E0138",                         \
      diagnostic_severity::error, { source_code_span if_keyword; },             \
      MESSAGE(QLJS_TRANSLATABLE("missing condition for if statement"),          \
              if_keyword))                                                      \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_missing_condition_for_while_statement, "E0139",                      \
      diagnostic_severity::error, { source_code_span while_keyword; },          \
      MESSAGE(QLJS_TRANSLATABLE("missing condition for while statement"),       \
              while_keyword))                                                   \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_missing_condition_for_switch_statement, "E0137",                     \
      diagnostic_severity::error, { source_code_span switch_keyword; },         \
      MESSAGE(QLJS_TRANSLATABLE("missing condition for switch statement"),      \
              switch_keyword))                                                  \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_missing_dots_for_attribute_spread, "E0186",                          \
      diagnostic_severity::error, { source_code_span expected_dots; },          \
      MESSAGE(QLJS_TRANSLATABLE("missing '...' in JSX attribute spread"),       \
              expected_dots))                                                   \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_missing_equal_after_variable, "E0202", diagnostic_severity::error,   \
      { source_code_span expected_equal; },                                     \
      MESSAGE(QLJS_TRANSLATABLE("missing '=' after variable"),                  \
              expected_equal))                                                  \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_missing_expression_between_parentheses, "E0078",                     \
      diagnostic_severity::error,                                               \
      {                                                                         \
        source_code_span left_paren_to_right_paren;                             \
        source_code_span left_paren;                                            \
        source_code_span right_paren;                                           \
      },                                                                        \
      MESSAGE(QLJS_TRANSLATABLE("missing expression between parentheses"),      \
              left_paren_to_right_paren))                                       \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_missing_for_loop_header, "E0125", diagnostic_severity::error,        \
      { source_code_span for_token; },                                          \
      MESSAGE(QLJS_TRANSLATABLE("missing header and body for 'for' loop"),      \
              for_token))                                                       \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_missing_for_loop_rhs_or_components_after_expression, "E0097",        \
      diagnostic_severity::error,                                               \
      {                                                                         \
        source_code_span header;                                                \
        source_code_span for_token;                                             \
      },                                                                        \
      MESSAGE(                                                                  \
          QLJS_TRANSLATABLE(                                                    \
              "for loop needs an iterable, or condition and update clauses"),   \
          header)                                                               \
          MESSAGE(                                                              \
              QLJS_TRANSLATABLE(                                                \
                  "use 'while' instead to loop until a condition is false"),    \
              for_token))                                                       \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_missing_for_loop_rhs_or_components_after_declaration, "E0098",       \
      diagnostic_severity::error,                                               \
      {                                                                         \
        source_code_span header;                                                \
        source_code_span for_token;                                             \
      },                                                                        \
      MESSAGE(                                                                  \
          QLJS_TRANSLATABLE(                                                    \
              "for loop needs an iterable, or condition and update clauses"),   \
          header))                                                              \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_missing_function_parameter_list, "E0073",                            \
      diagnostic_severity::error,                                               \
      { source_code_span expected_parameter_list; },                            \
      MESSAGE(QLJS_TRANSLATABLE("missing function parameter list"),             \
              expected_parameter_list))                                         \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_missing_function_body, "E0172", diagnostic_severity::error,          \
      { source_code_span expected_body; },                                      \
      MESSAGE(QLJS_TRANSLATABLE("missing body for function"), expected_body))   \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_missing_header_of_for_loop, "E0096", diagnostic_severity::error,     \
      { source_code_span where; },                                              \
      MESSAGE(QLJS_TRANSLATABLE("missing for loop header"), where))             \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_missing_initializer_in_const_declaration, "E0205",                   \
      diagnostic_severity::error, { source_code_span variable_name; },          \
      MESSAGE(QLJS_TRANSLATABLE("missing initializer in const declaration"),    \
              variable_name))                                                   \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_missing_key_for_object_entry, "E0154", diagnostic_severity::error,   \
      { source_code_span expression; },                                         \
      MESSAGE(QLJS_TRANSLATABLE(                                                \
                  "unexpected expression; missing key for object entry"),       \
              expression))                                                      \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_missing_class_method_name, "E0229", diagnostic_severity::error,      \
      { source_code_span expected_name; },                                      \
      MESSAGE(QLJS_TRANSLATABLE("missing name for class method"),               \
              expected_name))                                                   \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_missing_name_in_function_statement, "E0061",                         \
      diagnostic_severity::error, { source_code_span where; },                  \
      MESSAGE(QLJS_TRANSLATABLE("missing name in function statement"), where))  \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_missing_name_in_class_statement, "E0080",                            \
      diagnostic_severity::error, { source_code_span class_keyword; },          \
      MESSAGE(QLJS_TRANSLATABLE("missing name of class"), class_keyword))       \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_missing_name_of_exported_class, "E0081",                             \
      diagnostic_severity::error, { source_code_span class_keyword; },          \
      MESSAGE(QLJS_TRANSLATABLE("missing name of exported class"),              \
              class_keyword))                                                   \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_missing_name_of_exported_function, "E0079",                          \
      diagnostic_severity::error, { source_code_span function_keyword; },       \
      MESSAGE(QLJS_TRANSLATABLE("missing name of exported function"),           \
              function_keyword))                                                \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_missing_name_or_parentheses_for_function, "E0062",                   \
      diagnostic_severity::error,                                               \
      {                                                                         \
        source_code_span where;                                                 \
        source_code_span function;                                              \
      },                                                                        \
      MESSAGE(QLJS_TRANSLATABLE("missing name or parentheses for function"),    \
              where))                                                           \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_missing_operand_for_operator, "E0026", diagnostic_severity::error,   \
      { source_code_span where; },                                              \
      MESSAGE(QLJS_TRANSLATABLE("missing operand for operator"), where))        \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_missing_separator_between_object_type_entries, "E0257",              \
      diagnostic_severity::error, { source_code_span expected_separator; },     \
      MESSAGE(QLJS_TRANSLATABLE(                                                \
                  "missing ',', ';', or newline between object type entries"),  \
              expected_separator))                                              \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_redundant_delete_statement_on_variable, "E0086",                     \
      diagnostic_severity::warning, { source_code_span delete_expression; },    \
      MESSAGE(QLJS_TRANSLATABLE("redundant delete statement on variable"),      \
              delete_expression))                                               \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_missing_if_after_else, "E0184", diagnostic_severity::error,          \
      { source_code_span expected_if; },                                        \
      MESSAGE(QLJS_TRANSLATABLE("missing 'if' after 'else'"), expected_if))     \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_missing_operator_between_expression_and_arrow_function, "E0063",     \
      diagnostic_severity::error, { source_code_span where; },                  \
      MESSAGE(QLJS_TRANSLATABLE(                                                \
                  "missing operator between expression and arrow function"),    \
              where))                                                           \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_missing_parentheses_around_exponent_with_unary_lhs, "E0195",         \
      diagnostic_severity::error,                                               \
      {                                                                         \
        source_code_span exponent_expression;                                   \
        source_code_span unary_operator;                                        \
      },                                                                        \
      MESSAGE(                                                                  \
          QLJS_TRANSLATABLE("missing parentheses around operand of '{0}'"),     \
          exponent_expression)                                                  \
          MESSAGE(                                                              \
              QLJS_TRANSLATABLE("'{0}' operator cannot be used before '**' "    \
                                "without parentheses"),                         \
              unary_operator))                                                  \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_missing_parentheses_around_self_invoked_function, "E0211",           \
      diagnostic_severity::error,                                               \
      {                                                                         \
        source_code_span invocation;                                            \
        source_code_span func_start;                                            \
      },                                                                        \
      MESSAGE(QLJS_TRANSLATABLE(                                                \
                  "missing parentheses around self-invoked function"),          \
              invocation)                                                       \
          MESSAGE(QLJS_TRANSLATABLE("function starts here"), func_start))       \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_missing_parentheses_around_unary_lhs_of_exponent, "E0194",           \
      diagnostic_severity::error,                                               \
      {                                                                         \
        source_code_span unary_expression;                                      \
        source_code_span exponent_operator;                                     \
      },                                                                        \
      MESSAGE(QLJS_TRANSLATABLE(                                                \
                  "missing parentheses around left-hand side of '**'"),         \
              unary_expression)                                                 \
          MESSAGE(                                                              \
              QLJS_TRANSLATABLE("'**' operator cannot be used after unary "     \
                                "'{1}' without parentheses"),                   \
              exponent_operator, unary_expression))                             \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_missing_property_name_for_dot_operator, "E0142",                     \
      diagnostic_severity::error, { source_code_span dot; },                    \
      MESSAGE(QLJS_TRANSLATABLE("missing property name after '.' operator"),    \
              dot))                                                             \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_missing_semicolon_after_abstract_method, "E0293",                    \
      diagnostic_severity::error, { source_code_span expected_semicolon; },     \
      MESSAGE(QLJS_TRANSLATABLE("missing semicolon after abstract method"),     \
              expected_semicolon))                                              \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_missing_semicolon_after_declare_class_method, "E0334",               \
      diagnostic_severity::error, { source_code_span expected_semicolon; },     \
      MESSAGE(                                                                  \
          QLJS_TRANSLATABLE("missing semicolon after 'declare class' method"),  \
          expected_semicolon))                                                  \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_missing_semicolon_after_statement, "E0027",                          \
      diagnostic_severity::error, { source_code_span where; },                  \
      MESSAGE(QLJS_TRANSLATABLE("missing semicolon after statement"), where))   \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_missing_semicolon_after_field, "E0223", diagnostic_severity::error,  \
      { source_code_span expected_semicolon; },                                 \
      MESSAGE(QLJS_TRANSLATABLE("missing semicolon after field"),               \
              expected_semicolon))                                              \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_missing_semicolon_after_index_signature, "E0226",                    \
      diagnostic_severity::error, { source_code_span expected_semicolon; },     \
      MESSAGE(QLJS_TRANSLATABLE("missing semicolon after index signature"),     \
              expected_semicolon))                                              \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_missing_semicolon_after_interface_method, "E0292",                   \
      diagnostic_severity::error, { source_code_span expected_semicolon; },     \
      MESSAGE(QLJS_TRANSLATABLE("missing semicolon after interface method"),    \
              expected_semicolon))                                              \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_missing_semicolon_between_for_loop_condition_and_update, "E0100",    \
      diagnostic_severity::error, { source_code_span expected_semicolon; },     \
      MESSAGE(QLJS_TRANSLATABLE("missing semicolon between condition and "      \
                                "update parts of for loop"),                    \
              expected_semicolon))                                              \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_missing_semicolon_between_for_loop_init_and_condition, "E0099",      \
      diagnostic_severity::error, { source_code_span expected_semicolon; },     \
      MESSAGE(                                                                  \
          QLJS_TRANSLATABLE("missing semicolon between init and condition "     \
                            "parts of for loop"),                               \
          expected_semicolon))                                                  \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_missing_token_after_export, "E0113", diagnostic_severity::error,     \
      { source_code_span export_token; },                                       \
      MESSAGE(QLJS_TRANSLATABLE(                                                \
                  "incomplete export; expected 'export default ...' or "        \
                  "'export {{name}' or 'export * from ...' or 'export class' "  \
                  "or 'export function' or 'export let'"),                      \
              export_token))                                                    \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_missing_type_between_intersection_or_union, "E0258",                 \
      diagnostic_severity::error,                                               \
      {                                                                         \
        source_code_span left_operator;                                         \
        source_code_span right_operator;                                        \
      },                                                                        \
      MESSAGE(QLJS_TRANSLATABLE("missing type between '{1}' and '{0}'"),        \
              right_operator, left_operator))                                   \
                                                                                \
  /* TODO(strager): Make more specific errors, like 'missing type after :',     \
     'missing type after keyof', etc. */                                        \
  QLJS_DIAG_TYPE(                                                               \
      diag_missing_typescript_type, "E0284", diagnostic_severity::error,        \
      { source_code_span expected_type; },                                      \
      MESSAGE(QLJS_TRANSLATABLE("missing TypeScript type"), expected_type))     \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_missing_value_for_object_literal_entry, "E0083",                     \
      diagnostic_severity::error, { source_code_span key; },                    \
      MESSAGE(QLJS_TRANSLATABLE("missing value for object property"), key))     \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_missing_variable_name_in_declaration, "E0123",                       \
      diagnostic_severity::error, { source_code_span equal_token; },            \
      MESSAGE(QLJS_TRANSLATABLE("missing variable name"), equal_token))         \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_missing_while_and_condition_for_do_while_statement, "E0103",         \
      diagnostic_severity::error,                                               \
      {                                                                         \
        source_code_span do_token;                                              \
        source_code_span expected_while;                                        \
      },                                                                        \
      MESSAGE(QLJS_TRANSLATABLE(                                                \
                  "missing 'while (condition)' for do-while statement"),        \
              expected_while)                                                   \
          MESSAGE(QLJS_TRANSLATABLE("do-while statement starts here"),          \
                  do_token))                                                    \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_newline_not_allowed_between_async_and_parameter_list, "E0163",       \
      diagnostic_severity::error,                                               \
      {                                                                         \
        source_code_span async;                                                 \
        source_code_span arrow;                                                 \
      },                                                                        \
      MESSAGE(QLJS_TRANSLATABLE("newline is not allowed between 'async' and "   \
                                "arrow function parameter list"),               \
              async) MESSAGE(QLJS_TRANSLATABLE("arrow is here"), arrow))        \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_newline_not_allowed_between_async_and_function_keyword, "E0317",     \
      diagnostic_severity::error,                                               \
      {                                                                         \
        source_code_span async_keyword;                                         \
        source_code_span function_keyword;                                      \
      },                                                                        \
      MESSAGE(QLJS_TRANSLATABLE("newline is not allowed between 'async' and "   \
                                "'function'"),                                  \
              async_keyword)                                                    \
          MESSAGE(QLJS_TRANSLATABLE("'function' is here"), function_keyword))   \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_newline_not_allowed_after_abstract_keyword, "E0300",                 \
      diagnostic_severity::error, { source_code_span abstract_keyword; },       \
      MESSAGE(QLJS_TRANSLATABLE("newline is not allowed after 'abstract'"),     \
              abstract_keyword))                                                \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_newline_not_allowed_after_interface_keyword, "E0275",                \
      diagnostic_severity::error, { source_code_span interface_keyword; },      \
      MESSAGE(QLJS_TRANSLATABLE("newline is not allowed after 'interface'"),    \
              interface_keyword))                                               \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_newline_not_allowed_after_namespace_keyword, "E0276",                \
      diagnostic_severity::error, { source_code_span namespace_keyword; },      \
      MESSAGE(QLJS_TRANSLATABLE("newline is not allowed after '{0}'"),          \
              namespace_keyword))                                               \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_newline_not_allowed_after_type_keyword, "E0277",                     \
      diagnostic_severity::error, { source_code_span type_keyword; },           \
      MESSAGE(QLJS_TRANSLATABLE("newline is not allowed after 'type'"),         \
              type_keyword))                                                    \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_newline_not_allowed_before_assignment_assertion_operator, "E0241",   \
      diagnostic_severity::error,                                               \
      {                                                                         \
        source_code_span bang;                                                  \
        source_code_span field_name;                                            \
      },                                                                        \
      MESSAGE(QLJS_TRANSLATABLE(                                                \
                  "newline is not allowed between field name and '!'"),         \
              bang)                                                             \
          MESSAGE(QLJS_TRANSLATABLE("field declared here"), field_name))        \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_number_literal_contains_consecutive_underscores, "E0028",            \
      diagnostic_severity::error, { source_code_span underscores; },            \
      MESSAGE(QLJS_TRANSLATABLE(                                                \
                  "number literal contains consecutive underscores"),           \
              underscores))                                                     \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_number_literal_contains_trailing_underscores, "E0029",               \
      diagnostic_severity::error, { source_code_span underscores; },            \
      MESSAGE(                                                                  \
          QLJS_TRANSLATABLE("number literal contains trailing underscore(s)"),  \
          underscores))                                                         \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_octal_literal_may_not_have_exponent, "E0030",                        \
      diagnostic_severity::error, { source_code_span characters; },             \
      MESSAGE(QLJS_TRANSLATABLE("octal literal may not have exponent"),         \
              characters))                                                      \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_octal_literal_may_not_have_decimal, "E0031",                         \
      diagnostic_severity::error, { source_code_span characters; },             \
      MESSAGE(QLJS_TRANSLATABLE("octal literal may not have decimal"),          \
              characters))                                                      \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_object_literal_default_in_expression, "E0253",                       \
      diagnostic_severity::error, { source_code_span equal; },                  \
      MESSAGE(QLJS_TRANSLATABLE("use ':' instead of '=' in object literals"),   \
              equal))                                                           \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_optional_arrow_parameter_requires_parentheses, "E0311",              \
      diagnostic_severity::error,                                               \
      {                                                                         \
        source_code_span parameter_and_question;                                \
        source_code_span question;                                              \
      },                                                                        \
      MESSAGE(QLJS_TRANSLATABLE("missing parentheses around parameter"),        \
              parameter_and_question)                                           \
          MESSAGE(QLJS_TRANSLATABLE(                                            \
                      "TypeScript optional parameter requires parentheses"),    \
                  question))                                                    \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_optional_arrow_parameter_with_type_annotation_requires_parentheses,  \
      "E0312", diagnostic_severity::error,                                      \
      {                                                                         \
        source_code_span parameter_and_annotation;                              \
        source_code_span question;                                              \
        source_code_span type_colon;                                            \
      },                                                                        \
      MESSAGE(QLJS_TRANSLATABLE("missing parentheses around parameter"),        \
              parameter_and_annotation)                                         \
          MESSAGE(QLJS_TRANSLATABLE("TypeScript optional parameter with type "  \
                                    "annotation requires parentheses"),         \
                  question))                                                    \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_optional_parameter_cannot_have_initializer, "E0310",                 \
      diagnostic_severity::error,                                               \
      {                                                                         \
        source_code_span equal;                                                 \
        source_code_span question;                                              \
      },                                                                        \
      MESSAGE(QLJS_TRANSLATABLE("optional parameter cannot have both '?' and "  \
                                "initializer; remove '?'"),                     \
              question)                                                         \
          MESSAGE(QLJS_TRANSLATABLE("initializer starts here"), equal))         \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_integer_literal_will_lose_precision, "E0212",                        \
      diagnostic_severity::warning,                                             \
      {                                                                         \
        source_code_span characters;                                            \
        string8_view rounded_val;                                               \
      },                                                                        \
      MESSAGE(QLJS_TRANSLATABLE("integer cannot be represented and will be "    \
                                "rounded to '{1}'"),                            \
              characters, rounded_val))                                         \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_private_properties_are_not_allowed_in_object_literals, "E0156",      \
      diagnostic_severity::error, { identifier private_identifier; },           \
      MESSAGE(QLJS_TRANSLATABLE(                                                \
                  "private properties are not allowed in object literals"),     \
              private_identifier))                                              \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_readonly_static_field, "E0232", diagnostic_severity::error,          \
      { source_code_span readonly_static; },                                    \
      MESSAGE(QLJS_TRANSLATABLE("'readonly static' is not allowed; write "      \
                                "'static readonly' instead"),                   \
              readonly_static))                                                 \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_redeclaration_of_global_variable, "E0033",                           \
      diagnostic_severity::error, { identifier redeclaration; },                \
      MESSAGE(QLJS_TRANSLATABLE("redeclaration of global variable"),            \
              redeclaration))                                                   \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_redeclaration_of_variable, "E0034", diagnostic_severity::error,      \
      {                                                                         \
        identifier redeclaration;                                               \
        identifier original_declaration;                                        \
      },                                                                        \
      MESSAGE(QLJS_TRANSLATABLE("redeclaration of variable: {0}"),              \
              redeclaration)                                                    \
          MESSAGE(QLJS_TRANSLATABLE("variable already declared here"),          \
                  original_declaration))                                        \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_redundant_await, "E0266", diagnostic_severity::warning,              \
      { source_code_span await_operator; },                                     \
      MESSAGE(QLJS_TRANSLATABLE("redundant 'await'"), await_operator))          \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_regexp_literal_flags_cannot_contain_unicode_escapes, "E0035",        \
      diagnostic_severity::error, { source_code_span escape_sequence; },        \
      MESSAGE(QLJS_TRANSLATABLE(                                                \
                  "RegExp literal flags cannot contain Unicode escapes"),       \
              escape_sequence))                                                 \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_return_statement_returns_nothing, "E0179",                           \
      diagnostic_severity::warning, { source_code_span return_keyword; },       \
      MESSAGE(                                                                  \
          QLJS_TRANSLATABLE("return statement returns nothing (undefined)"),    \
          return_keyword))                                                      \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_spread_parameter_cannot_be_this, "E0304",                            \
      diagnostic_severity::error,                                               \
      {                                                                         \
        source_code_span this_keyword;                                          \
        source_code_span spread_operator;                                       \
      },                                                                        \
      MESSAGE(QLJS_TRANSLATABLE("cannot use '...' on 'this' parameter"),        \
              spread_operator))                                                 \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_statement_before_first_switch_case, "E0198",                         \
      diagnostic_severity::error, { source_code_span unexpected_statement; },   \
      MESSAGE(QLJS_TRANSLATABLE("unexpected statement before first switch "     \
                                "case, expected 'case' or 'default'"),          \
              unexpected_statement))                                            \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_stray_comma_in_let_statement, "E0036", diagnostic_severity::error,   \
      { source_code_span where; },                                              \
      MESSAGE(QLJS_TRANSLATABLE("stray comma in let statement"), where))        \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_stray_comma_in_parameter, "E0180", diagnostic_severity::error,       \
      { source_code_span comma; },                                              \
      MESSAGE(QLJS_TRANSLATABLE("stray comma in function parameter"), comma))   \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_string_namespace_name_is_only_allowed_with_declare_module, "E0359",  \
      diagnostic_severity::error, { source_code_span module_name; },            \
      MESSAGE(QLJS_TRANSLATABLE("string module name is only allowed with "      \
                                "'declare module'"),                            \
              module_name))                                                     \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_string_namespace_name_is_only_allowed_at_top_level, "E0361",         \
      diagnostic_severity::error, { source_code_span module_name; },            \
      MESSAGE(QLJS_TRANSLATABLE(                                                \
                  "module with string name is only allowed at the top level"),  \
              module_name))                                                     \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_this_parameter_must_be_first, "E0303", diagnostic_severity::error,   \
      {                                                                         \
        source_code_span this_keyword;                                          \
        source_code_span first_parameter_begin;                                 \
      },                                                                        \
      MESSAGE(QLJS_TRANSLATABLE("'this' must be the first parameter"),          \
              this_keyword)                                                     \
          MESSAGE(QLJS_TRANSLATABLE("first parameter starts here"),             \
                  first_parameter_begin))                                       \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_this_parameter_not_allowed_in_arrow_functions, "E0301",              \
      diagnostic_severity::error, { source_code_span this_keyword; },           \
      MESSAGE(QLJS_TRANSLATABLE(                                                \
                  "'this' parameters are not allowed in arrow functions"),      \
              this_keyword))                                                    \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_this_parameter_not_allowed_in_javascript, "E0305",                   \
      diagnostic_severity::error, { source_code_span this_keyword; },           \
      MESSAGE(QLJS_TRANSLATABLE(                                                \
                  "'this' parameters are not allowed in JavaScript"),           \
              this_keyword))                                                    \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_this_parameter_not_allowed_when_destructuring, "E0302",              \
      diagnostic_severity::error, { source_code_span this_keyword; },           \
      MESSAGE(QLJS_TRANSLATABLE(                                                \
                  "'this' parameter not allowed when destructuring"),           \
              this_keyword))                                                    \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_typescript_abstract_class_not_allowed_in_javascript, "E0244",        \
      diagnostic_severity::error, { source_code_span abstract_keyword; },       \
      MESSAGE(QLJS_TRANSLATABLE("{0} classes are not allowed in JavaScript"),   \
              abstract_keyword))                                                \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_typescript_angle_type_assertion_not_allowed_in_tsx, "E0283",         \
      diagnostic_severity::error,                                               \
      {                                                                         \
        source_code_span bracketed_type;                                        \
        source_code_span expected_as;                                           \
      },                                                                        \
      MESSAGE(QLJS_TRANSLATABLE("TypeScript <Type> type assertions are not "    \
                                "allowed in JSX mode"),                         \
              bracketed_type)                                                   \
          MESSAGE(QLJS_TRANSLATABLE(                                            \
                      "write the type assertion with 'as' here instead"),       \
                  expected_as))                                                 \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_typescript_as_const_with_non_literal_typeable, "E0291",              \
      diagnostic_severity::error,                                               \
      {                                                                         \
        source_code_span expression;                                            \
        source_code_span as_const;                                              \
      },                                                                        \
      MESSAGE(                                                                  \
          QLJS_TRANSLATABLE("'as const' is only allowed on literals (array, "   \
                            "object, string, boolean) and enum members"),       \
          expression)                                                           \
          MESSAGE(QLJS_TRANSLATABLE("'as const' located here"), as_const))      \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_typescript_as_type_assertion_not_allowed_in_javascript, "E0281",     \
      diagnostic_severity::error, { source_code_span as_keyword; },             \
      MESSAGE(QLJS_TRANSLATABLE("TypeScript 'as' type assertions are not "      \
                                "allowed in JavaScript"),                       \
              as_keyword))                                                      \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_typescript_as_or_satisfies_used_for_parameter_type_annotation,       \
      "E0282", diagnostic_severity::error, { source_code_span bad_keyword; },   \
      MESSAGE(QLJS_TRANSLATABLE(                                                \
                  "use ':' instead of '{0}' to type a function parameter"),     \
              bad_keyword))                                                     \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_typescript_assignment_asserted_fields_not_allowed_in_declare_class,  \
      "E0336", diagnostic_severity::error, { source_code_span bang; },          \
      MESSAGE(QLJS_TRANSLATABLE("assignment-asserted fields are "               \
                                "not allowed in 'declare class'"),              \
              bang))                                                            \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_typescript_assignment_asserted_fields_not_allowed_in_interfaces,     \
      "E0238", diagnostic_severity::error, { source_code_span bang; },          \
      MESSAGE(QLJS_TRANSLATABLE("assignment-asserted fields are "               \
                                "not supported in interfaces"),                 \
              bang))                                                            \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_typescript_assignment_asserted_fields_not_allowed_in_javascript,     \
      "E0239", diagnostic_severity::error, { source_code_span bang; },          \
      MESSAGE(QLJS_TRANSLATABLE("TypeScript assignment-asserted fields are "    \
                                "not supported in JavaScript"),                 \
              bang))                                                            \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_typescript_assignment_asserted_field_cannot_have_initializer,        \
      "E0290", diagnostic_severity::error,                                      \
      {                                                                         \
        source_code_span equal;                                                 \
        source_code_span bang;                                                  \
      },                                                                        \
      MESSAGE(QLJS_TRANSLATABLE(                                                \
                  "assignment-assertion fields cannot have default values"),    \
              equal)                                                            \
          MESSAGE(                                                              \
              QLJS_TRANSLATABLE("here is the assignment assertion operator"),   \
              bang))                                                            \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_typescript_assignment_asserted_field_must_have_a_type, "E0236",      \
      diagnostic_severity::error, { source_code_span bang; },                   \
      MESSAGE(QLJS_TRANSLATABLE(                                                \
                  "assignment-asserted field must have a type annotation"),     \
              bang))                                                            \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_typescript_assignment_asserted_method, "E0240",                      \
      diagnostic_severity::error, { source_code_span bang; },                   \
      MESSAGE(QLJS_TRANSLATABLE("'{0}' is not allowed on methods"), bang))      \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_typescript_catch_type_annotation_must_be_any, "E0256",               \
      diagnostic_severity::error, { source_code_span type_expression; },        \
      MESSAGE(                                                                  \
          QLJS_TRANSLATABLE(                                                    \
              "catch variable can only be typed as '*', 'any', or 'unknown'"),  \
          type_expression))                                                     \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_typescript_class_implements_not_allowed_in_javascript, "E0247",      \
      diagnostic_severity::error, { source_code_span implements_keyword; },     \
      MESSAGE(QLJS_TRANSLATABLE(                                                \
                  "TypeScript 'implements' is not allowed in JavaScript"),      \
              implements_keyword))                                              \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_typescript_delete_cannot_delete_variables, "E0325",                  \
      diagnostic_severity::error, { source_code_span delete_expression; },      \
      MESSAGE(QLJS_TRANSLATABLE("cannot delete variables in TypeScript"),       \
              delete_expression))                                               \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_typescript_enum_auto_member_needs_initializer_after_computed,        \
      "E0252", diagnostic_severity::error,                                      \
      {                                                                         \
        source_code_span auto_member_name;                                      \
        source_code_span computed_expression;                                   \
      },                                                                        \
      MESSAGE(QLJS_TRANSLATABLE("enum member needs initializer"),               \
              auto_member_name)                                                 \
          MESSAGE(                                                              \
              QLJS_TRANSLATABLE("computed value disables enum autoincrement"),  \
              computed_expression))                                             \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_typescript_enum_computed_name_must_be_simple, "E0249",               \
      diagnostic_severity::error, { source_code_span expression; },             \
      MESSAGE(QLJS_TRANSLATABLE(                                                \
                  "computed enum member name must be a simple string"),         \
              expression))                                                      \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_typescript_enum_is_not_allowed_in_javascript, "E0127",               \
      diagnostic_severity::error, { source_code_span enum_keyword; },           \
      MESSAGE(QLJS_TRANSLATABLE(                                                \
                  "TypeScript's 'enum' feature is not allowed in JavaScript"),  \
              enum_keyword))                                                    \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_typescript_enum_member_name_cannot_be_number, "E0250",               \
      diagnostic_severity::error, { source_code_span number; },                 \
      MESSAGE(QLJS_TRANSLATABLE("enum member name cannot be numeric"),          \
              number))                                                          \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_typescript_enum_value_must_be_constant, "E0251",                     \
      diagnostic_severity::error,                                               \
      {                                                                         \
        source_code_span expression;                                            \
        enum_kind declared_enum_kind;                                           \
      },                                                                        \
      MESSAGE(QLJS_TRANSLATABLE(                                                \
                  "{1:headlinese} value must be a compile-time constant"),      \
              expression, declared_enum_kind))                                  \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_typescript_implements_must_be_after_extends, "E0246",                \
      diagnostic_severity::error,                                               \
      {                                                                         \
        source_code_span implements_keyword;                                    \
        source_code_span extends_keyword;                                       \
      },                                                                        \
      MESSAGE(QLJS_TRANSLATABLE("'extends' must be before 'implements'"),       \
              extends_keyword)                                                  \
          MESSAGE(QLJS_TRANSLATABLE(                                            \
                      "move the 'extends' clause before 'implements' here"),    \
                  implements_keyword))                                          \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_typescript_import_alias_not_allowed_in_javascript, "E0274",          \
      diagnostic_severity::error,                                               \
      {                                                                         \
        source_code_span import_keyword;                                        \
        source_code_span equal;                                                 \
      },                                                                        \
      MESSAGE(QLJS_TRANSLATABLE(                                                \
                  "TypeScript import aliases are not allowed in JavaScript"),   \
              equal)                                                            \
          MESSAGE(QLJS_TRANSLATABLE("write 'const' instead of '{0}' here"),     \
                  import_keyword))                                              \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_typescript_index_signature_cannot_be_method, "E0227",                \
      diagnostic_severity::error, { source_code_span left_paren; },             \
      MESSAGE(                                                                  \
          QLJS_TRANSLATABLE("index signature must be a field, not a method"),   \
          left_paren))                                                          \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_typescript_index_signature_needs_type, "E0225",                      \
      diagnostic_severity::error, { source_code_span expected_type; },          \
      MESSAGE(QLJS_TRANSLATABLE("index signatures require a value type"),       \
              expected_type))                                                   \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_typescript_infer_outside_conditional_type, "E0367",                  \
      diagnostic_severity::error, { source_code_span infer_keyword; },          \
      MESSAGE(QLJS_TRANSLATABLE("'infer' is only allowed between 'extends' "    \
                                "and '?' in conditional types"),                \
              infer_keyword))                                                   \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_typescript_infer_requires_parentheses, "E0366",                      \
      diagnostic_severity::error,                                               \
      {                                                                         \
        source_code_span infer_and_type;                                        \
        identifier type;                                                        \
      },                                                                        \
      MESSAGE(                                                                  \
          QLJS_TRANSLATABLE("parentheses are required around 'infer {1}'"),     \
          infer_and_type, type))                                                \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_typescript_function_overload_signature_must_have_same_name,          \
      "E0316", diagnostic_severity::error,                                      \
      {                                                                         \
        identifier overload_name;                                               \
        identifier function_name;                                               \
      },                                                                        \
      MESSAGE(QLJS_TRANSLATABLE(                                                \
                  "function overload signature must be named '{1}'"),           \
              overload_name, function_name)                                     \
          MESSAGE(                                                              \
              QLJS_TRANSLATABLE("overloaded function '{0}' declared here"),     \
              function_name))                                                   \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_typescript_function_overload_signature_must_not_have_generator_star, \
      "E0318", diagnostic_severity::error,                                      \
      { source_code_span generator_star; },                                     \
      MESSAGE(QLJS_TRANSLATABLE(                                                \
                  "function overload signature cannot have generator '*'"),     \
              generator_star))                                                  \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_typescript_generic_arrow_needs_comma_in_jsx_mode, "E0285",           \
      diagnostic_severity::error,                                               \
      {                                                                         \
        source_code_span generic_parameters_less;                               \
        source_code_span expected_comma;                                        \
        source_code_span arrow;                                                 \
      },                                                                        \
      MESSAGE(                                                                  \
          QLJS_TRANSLATABLE("generic arrow function needs ',' here in TSX"),    \
          expected_comma))                                                      \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_typescript_generic_parameter_list_is_empty, "E0264",                 \
      diagnostic_severity::error, { source_code_span expected_parameter; },     \
      MESSAGE(                                                                  \
          QLJS_TRANSLATABLE(                                                    \
              "expected at least one parameter in generic parameter list"),     \
          expected_parameter))                                                  \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_typescript_generics_not_allowed_in_javascript, "E0233",              \
      diagnostic_severity::error, { source_code_span opening_less; },           \
      MESSAGE(QLJS_TRANSLATABLE("TypeScript generics are not "                  \
                                "allowed in JavaScript code"),                  \
              opening_less))                                                    \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_typescript_type_export_not_allowed_in_javascript, "E0278",           \
      diagnostic_severity::error, { source_code_span type_keyword; },           \
      MESSAGE(QLJS_TRANSLATABLE("TypeScript type exports are not "              \
                                "allowed in JavaScript"),                       \
              type_keyword))                                                    \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_typescript_inline_type_export_not_allowed_in_type_only_export,       \
      "E0280", diagnostic_severity::error,                                      \
      {                                                                         \
        source_code_span inline_type_keyword;                                   \
        source_code_span type_only_keyword;                                     \
      },                                                                        \
      MESSAGE(QLJS_TRANSLATABLE("'type' cannot be used twice in export"),       \
              inline_type_keyword)                                              \
          MESSAGE(QLJS_TRANSLATABLE("remove this 'type'"), type_only_keyword))  \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_typescript_inline_type_import_not_allowed_in_type_only_import,       \
      "E0272", diagnostic_severity::error,                                      \
      {                                                                         \
        source_code_span inline_type_keyword;                                   \
        source_code_span type_only_keyword;                                     \
      },                                                                        \
      MESSAGE(QLJS_TRANSLATABLE("'type' cannot be used twice in import"),       \
              inline_type_keyword)                                              \
          MESSAGE(QLJS_TRANSLATABLE("remove this 'type'"), type_only_keyword))  \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_typescript_interfaces_cannot_contain_static_blocks, "E0243",         \
      diagnostic_severity::error, { source_code_span static_token; },           \
      MESSAGE(QLJS_TRANSLATABLE("interfaces cannot contain static blocks"),     \
              static_token))                                                    \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_typescript_declare_class_cannot_contain_static_block_statement,      \
      "E0332", diagnostic_severity::error, { source_code_span static_token; },  \
      MESSAGE(                                                                  \
          QLJS_TRANSLATABLE("'declare class' cannot contain static block"),     \
          static_token))                                                        \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_typescript_interfaces_not_allowed_in_javascript, "E0213",            \
      diagnostic_severity::error, { source_code_span interface_keyword; },      \
      MESSAGE(QLJS_TRANSLATABLE("TypeScript's 'interface' feature is not "      \
                                "allowed in JavaScript code"),                  \
              interface_keyword))                                               \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_typescript_missing_name_and_colon_in_named_tuple_type, "E0319",      \
      diagnostic_severity::error,                                               \
      {                                                                         \
        source_code_span expected_name_and_colon;                               \
        source_code_span existing_name;                                         \
      },                                                                        \
      MESSAGE(                                                                  \
          QLJS_TRANSLATABLE("missing name for element in named tuple type"),    \
          expected_name_and_colon)                                              \
          MESSAGE(                                                              \
              QLJS_TRANSLATABLE("this tuple type is a named tuple type "        \
                                "because at least one element has a name"),     \
              existing_name))                                                   \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_typescript_missing_name_in_named_tuple_type, "E0320",                \
      diagnostic_severity::error, { source_code_span colon; },                  \
      MESSAGE(                                                                  \
          QLJS_TRANSLATABLE("missing name for element in named tuple type"),    \
          colon))                                                               \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_typescript_named_tuple_element_question_after_name_and_type,         \
      "E0322", diagnostic_severity::error,                                      \
      {                                                                         \
        source_code_span type_question;                                         \
        source_code_span name_question;                                         \
      },                                                                        \
      MESSAGE(QLJS_TRANSLATABLE("'?' belongs only after the tuple element "     \
                                "name, not also after the type"),               \
              type_question))                                                   \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_typescript_named_tuple_element_question_after_type, "E0314",         \
      diagnostic_severity::error,                                               \
      {                                                                         \
        source_code_span question;                                              \
        source_code_span expected_question;                                     \
      },                                                                        \
      MESSAGE(                                                                  \
          QLJS_TRANSLATABLE(                                                    \
              "'?' belongs after the tuple element name, not after the type"),  \
          question)                                                             \
          MESSAGE(QLJS_TRANSLATABLE("'?' goes here"), expected_question))       \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_typescript_named_tuple_element_spread_before_name_and_type,          \
      "E0329", diagnostic_severity::error,                                      \
      {                                                                         \
        source_code_span type_spread;                                           \
        source_code_span name_spread;                                           \
      },                                                                        \
      MESSAGE(QLJS_TRANSLATABLE("'...' belongs only before the tuple element "  \
                                "name, not also before the type"),              \
              type_spread))                                                     \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_typescript_named_tuple_element_spread_before_type, "E0328",          \
      diagnostic_severity::error,                                               \
      {                                                                         \
        source_code_span spread;                                                \
        source_code_span expected_spread;                                       \
      },                                                                        \
      MESSAGE(QLJS_TRANSLATABLE("'...' belongs before the tuple element "       \
                                "name, not before the type"),                   \
              spread)                                                           \
          MESSAGE(QLJS_TRANSLATABLE("'...' goes here"), expected_spread))       \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_typescript_namespaces_not_allowed_in_javascript, "E0273",            \
      diagnostic_severity::error, { source_code_span namespace_keyword; },      \
      MESSAGE(QLJS_TRANSLATABLE(                                                \
                  "TypeScript namespaces are not allowed in JavaScript"),       \
              namespace_keyword))                                               \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_typescript_non_null_assertion_not_allowed_in_javascript, "E0261",    \
      diagnostic_severity::error, { source_code_span bang; },                   \
      MESSAGE(                                                                  \
          QLJS_TRANSLATABLE(                                                    \
              "TypeScript non-null assertions are not allowed in JavaScript"),  \
          bang))                                                                \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_typescript_optional_parameters_not_allowed_in_javascript, "E0308",   \
      diagnostic_severity::error, { source_code_span question; },               \
      MESSAGE(                                                                  \
          QLJS_TRANSLATABLE(                                                    \
              "TypeScript optional parameters are not allowed in JavaScript"),  \
          question))                                                            \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_typescript_optional_properties_not_allowed_in_javascript, "E0228",   \
      diagnostic_severity::error, { source_code_span question; },               \
      MESSAGE(QLJS_TRANSLATABLE("TypeScript optional properties are not "       \
                                "allowed in JavaScript code"),                  \
              question))                                                        \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_typescript_optional_tuple_element_cannot_follow_spread_element,      \
      "E0323", diagnostic_severity::error,                                      \
      {                                                                         \
        source_code_span optional_question;                                     \
        source_code_span previous_spread;                                       \
      },                                                                        \
      MESSAGE(                                                                  \
          QLJS_TRANSLATABLE(                                                    \
              "optional tuple elements cannot come after spread elements"),     \
          optional_question)                                                    \
          MESSAGE(QLJS_TRANSLATABLE("prior spread element is here"),            \
                  previous_spread))                                             \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_typescript_private_not_allowed_in_javascript, "E0222",               \
      diagnostic_severity::error, { source_code_span specifier; },              \
      MESSAGE(QLJS_TRANSLATABLE("'private' is not allowed in JavaScript"),      \
              specifier))                                                       \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_typescript_protected_not_allowed_in_javascript, "E0234",             \
      diagnostic_severity::error, { source_code_span specifier; },              \
      MESSAGE(QLJS_TRANSLATABLE("'protected' is not allowed in JavaScript"),    \
              specifier))                                                       \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_typescript_public_not_allowed_in_javascript, "E0289",                \
      diagnostic_severity::error, { source_code_span specifier; },              \
      MESSAGE(QLJS_TRANSLATABLE("'public' is not allowed in JavaScript"),       \
              specifier))                                                       \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_typescript_readonly_fields_not_allowed_in_javascript, "E0230",       \
      diagnostic_severity::error, { source_code_span readonly_keyword; },       \
      MESSAGE(QLJS_TRANSLATABLE("TypeScript's 'readonly' feature is not "       \
                                "allowed in JavaScript code"),                  \
              readonly_keyword))                                                \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_typescript_readonly_method, "E0231", diagnostic_severity::error,     \
      { source_code_span readonly_keyword; },                                   \
      MESSAGE(QLJS_TRANSLATABLE("methods cannot be readonly"),                  \
              readonly_keyword))                                                \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_typescript_readonly_in_type_needs_array_or_tuple_type, "E0313",      \
      diagnostic_severity::error, { source_code_span readonly_keyword; },       \
      MESSAGE(QLJS_TRANSLATABLE(                                                \
                  "'readonly' only works with array types and tuple types"),    \
              readonly_keyword))                                                \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_typescript_required_tuple_element_after_optional_element, "E0321",   \
      diagnostic_severity::error,                                               \
      {                                                                         \
        source_code_span expected_question;                                     \
        source_code_span previous_optional_question;                            \
      },                                                                        \
      MESSAGE(                                                                  \
          QLJS_TRANSLATABLE("expected '?' to mark tuple element as optional"),  \
          expected_question)                                                    \
          MESSAGE(QLJS_TRANSLATABLE("only optional tuple elements can follow "  \
                                    "this optional tuple element"),             \
                  previous_optional_question))                                  \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_typescript_requires_space_between_greater_and_equal, "E0365",        \
      diagnostic_severity::error, { source_code_span greater_equal; },          \
      MESSAGE(QLJS_TRANSLATABLE(                                                \
                  "TypeScript requires whitespace between '>' and '=' here"),   \
              greater_equal))                                                   \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_typescript_satisfies_not_allowed_in_javascript, "E0364",             \
      diagnostic_severity::error, { source_code_span satisfies_keyword; },      \
      MESSAGE(QLJS_TRANSLATABLE("TypeScript 'satisfies' operator is not "       \
                                "allowed in JavaScript"),                       \
              satisfies_keyword))                                               \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_typescript_type_annotation_in_expression, "E0254",                   \
      diagnostic_severity::error, { source_code_span type_colon; },             \
      MESSAGE(QLJS_TRANSLATABLE(                                                \
                  "unexpected ':' in expression; did you mean 'as'?"),          \
              type_colon))                                                      \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_typescript_type_annotations_not_allowed_in_javascript, "E0224",      \
      diagnostic_severity::error, { source_code_span type_colon; },             \
      MESSAGE(QLJS_TRANSLATABLE("TypeScript type annotations are not "          \
                                "allowed in JavaScript code"),                  \
              type_colon))                                                      \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_typescript_type_alias_not_allowed_in_javascript, "E0267",            \
      diagnostic_severity::error, { source_code_span type_keyword; },           \
      MESSAGE(                                                                  \
          QLJS_TRANSLATABLE("TypeScript types are not allowed in JavaScript"),  \
          type_keyword))                                                        \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_typescript_type_only_import_cannot_import_default_and_named,         \
      "E0268", diagnostic_severity::error, { source_code_span type_keyword; },  \
      MESSAGE(QLJS_TRANSLATABLE("TypeScript type imports cannot import both "   \
                                "default and named exports"),                   \
              type_keyword))                                                    \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_typescript_type_import_not_allowed_in_javascript, "E0270",           \
      diagnostic_severity::error, { source_code_span type_keyword; },           \
      MESSAGE(QLJS_TRANSLATABLE("TypeScript type imports are not "              \
                                "allowed in JavaScript"),                       \
              type_keyword))                                                    \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_typescript_spread_element_cannot_be_optional, "E0324",               \
      diagnostic_severity::error,                                               \
      {                                                                         \
        source_code_span optional_question;                                     \
        source_code_span spread;                                                \
      },                                                                        \
      MESSAGE(QLJS_TRANSLATABLE("spread tuple elements cannot be optional"),    \
              optional_question)                                                \
          MESSAGE(QLJS_TRANSLATABLE("spread starts here"), spread))             \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_typescript_style_const_field, "E0165", diagnostic_severity::error,   \
      { source_code_span const_token; },                                        \
      MESSAGE(QLJS_TRANSLATABLE("const fields within classes are only "         \
                                "allowed in TypeScript, not JavaScript"),       \
              const_token))                                                     \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_typescript_variance_keywords_in_wrong_order, "E0368",                \
      diagnostic_severity::error,                                               \
      {                                                                         \
        source_code_span in_keyword;                                            \
        source_code_span out_keyword;                                           \
      },                                                                        \
      MESSAGE(QLJS_TRANSLATABLE(                                                \
                  "'out in' is not allowed; write 'in out' instead"),           \
              in_keyword))                                                      \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_unclosed_block_comment, "E0037", diagnostic_severity::error,         \
      { source_code_span comment_open; },                                       \
      MESSAGE(QLJS_TRANSLATABLE("unclosed block comment"), comment_open))       \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_unclosed_class_block, "E0199", diagnostic_severity::error,           \
      { source_code_span block_open; },                                         \
      MESSAGE(                                                                  \
          QLJS_TRANSLATABLE("unclosed class; expected '}' by end of file"),     \
          block_open))                                                          \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_unclosed_code_block, "E0134", diagnostic_severity::error,            \
      { source_code_span block_open; },                                         \
      MESSAGE(QLJS_TRANSLATABLE(                                                \
                  "unclosed code block; expected '}' by end of file"),          \
              block_open))                                                      \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_unclosed_interface_block, "E0215", diagnostic_severity::error,       \
      { source_code_span block_open; },                                         \
      MESSAGE(QLJS_TRANSLATABLE(                                                \
                  "unclosed interface; expected '}' by end of file"),           \
              block_open))                                                      \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_unclosed_identifier_escape_sequence, "E0038",                        \
      diagnostic_severity::error, { source_code_span escape_sequence; },        \
      MESSAGE(QLJS_TRANSLATABLE("unclosed identifier escape sequence"),         \
              escape_sequence))                                                 \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_unclosed_object_literal, "E0161", diagnostic_severity::error,        \
      {                                                                         \
        source_code_span object_open;                                           \
        source_code_span expected_object_close;                                 \
      },                                                                        \
      MESSAGE(QLJS_TRANSLATABLE("unclosed object literal; expected '}'"),       \
              expected_object_close)                                            \
          MESSAGE(QLJS_TRANSLATABLE("object literal started here"),             \
                  object_open))                                                 \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_unclosed_regexp_literal, "E0039", diagnostic_severity::error,        \
      { source_code_span regexp_literal; },                                     \
      MESSAGE(QLJS_TRANSLATABLE("unclosed regexp literal"), regexp_literal))    \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_unclosed_string_literal, "E0040", diagnostic_severity::error,        \
      { source_code_span string_literal; },                                     \
      MESSAGE(QLJS_TRANSLATABLE("unclosed string literal"), string_literal))    \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_unclosed_jsx_string_literal, "E0181", diagnostic_severity::error,    \
      { source_code_span string_literal_begin; },                               \
      MESSAGE(QLJS_TRANSLATABLE("unclosed string literal"),                     \
              string_literal_begin))                                            \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_unclosed_template, "E0041", diagnostic_severity::error,              \
      { source_code_span incomplete_template; },                                \
      MESSAGE(QLJS_TRANSLATABLE("unclosed template"), incomplete_template))     \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_unexpected_at_character, "E0042", diagnostic_severity::error,        \
      { source_code_span character; },                                          \
      MESSAGE(QLJS_TRANSLATABLE("unexpected '@'"), character))                  \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_unexpected_arrow_after_expression, "E0160",                          \
      diagnostic_severity::error,                                               \
      {                                                                         \
        source_code_span arrow;                                                 \
        source_code_span expression;                                            \
      },                                                                        \
      MESSAGE(QLJS_TRANSLATABLE("unexpected '{0}'"), arrow)                     \
          MESSAGE(QLJS_TRANSLATABLE("expected parameter for arrow function, "   \
                                    "but got an expression instead"),           \
                  expression))                                                  \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_unexpected_arrow_after_literal, "E0158",                             \
      diagnostic_severity::error,                                               \
      {                                                                         \
        source_code_span arrow;                                                 \
        source_code_span literal_parameter;                                     \
      },                                                                        \
      MESSAGE(QLJS_TRANSLATABLE("unexpected '{0}'"), arrow)                     \
          MESSAGE(QLJS_TRANSLATABLE("expected parameter for arrow function, "   \
                                    "but got a literal instead"),               \
                  literal_parameter))                                           \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_unexpected_backslash_in_identifier, "E0043",                         \
      diagnostic_severity::error, { source_code_span backslash; },              \
      MESSAGE(QLJS_TRANSLATABLE("unexpected '\\' in identifier"), backslash))   \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_unexpected_case_outside_switch_statement, "E0115",                   \
      diagnostic_severity::error, { source_code_span case_token; },             \
      MESSAGE(QLJS_TRANSLATABLE("unexpected 'case' outside switch statement"),  \
              case_token))                                                      \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_unexpected_characters_in_number, "E0044",                            \
      diagnostic_severity::error, { source_code_span characters; },             \
      MESSAGE(QLJS_TRANSLATABLE("unexpected characters in number literal"),     \
              characters))                                                      \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_unexpected_control_character, "E0045", diagnostic_severity::error,   \
      { source_code_span character; },                                          \
      MESSAGE(QLJS_TRANSLATABLE("unexpected control character"), character))    \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_unexpected_characters_in_binary_number, "E0046",                     \
      diagnostic_severity::error, { source_code_span characters; },             \
      MESSAGE(QLJS_TRANSLATABLE("unexpected characters in binary literal"),     \
              characters))                                                      \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_unexpected_characters_in_octal_number, "E0047",                      \
      diagnostic_severity::error, { source_code_span characters; },             \
      MESSAGE(QLJS_TRANSLATABLE("unexpected characters in octal literal"),      \
              characters))                                                      \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_unexpected_characters_in_hex_number, "E0048",                        \
      diagnostic_severity::error, { source_code_span characters; },             \
      MESSAGE(QLJS_TRANSLATABLE("unexpected characters in hex literal"),        \
              characters))                                                      \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_unexpected_default_outside_switch_statement, "E0116",                \
      diagnostic_severity::error, { source_code_span default_token; },          \
      MESSAGE(                                                                  \
          QLJS_TRANSLATABLE("unexpected 'default' outside switch statement"),   \
          default_token))                                                       \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_unexpected_greater_in_jsx_text, "E0182",                             \
      diagnostic_severity::error, { source_code_span greater; },                \
      MESSAGE(QLJS_TRANSLATABLE("'>' is not allowed directly in JSX text; "     \
                                "write {{'>'} or &gt; instead"),                \
              greater))                                                         \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_unexpected_literal_in_parameter_list, "E0159",                       \
      diagnostic_severity::error, { source_code_span literal; },                \
      MESSAGE(QLJS_TRANSLATABLE("unexpected literal in parameter list; "        \
                                "expected parameter name"),                     \
              literal))                                                         \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_unexpected_right_curly_in_jsx_text, "E0183",                         \
      diagnostic_severity::error, { source_code_span right_curly; },            \
      MESSAGE(QLJS_TRANSLATABLE("'}' is not allowed directly in JSX text; "     \
                                "write {{'}'} instead"),                        \
              right_curly))                                                     \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_unexpected_question_in_expression, "E0307",                          \
      diagnostic_severity::error, { source_code_span question; },               \
      MESSAGE(QLJS_TRANSLATABLE("unexpected '?'"), question))                   \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_unexpected_question_when_destructuring, "E0309",                     \
      diagnostic_severity::error, { source_code_span question; },               \
      MESSAGE(QLJS_TRANSLATABLE("unexpected '?' when destructuring"),           \
              question))                                                        \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_unexpected_semicolon_in_c_style_for_loop, "E0102",                   \
      diagnostic_severity::error, { source_code_span semicolon; },              \
      MESSAGE(QLJS_TRANSLATABLE("C-style for loops have only three "            \
                                "semicolon-separated components"),              \
              semicolon))                                                       \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_unexpected_semicolon_in_for_in_loop, "E0110",                        \
      diagnostic_severity::error, { source_code_span semicolon; },              \
      MESSAGE(                                                                  \
          QLJS_TRANSLATABLE("for-in loop expression cannot have semicolons"),   \
          semicolon))                                                           \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_unexpected_semicolon_in_for_of_loop, "E0109",                        \
      diagnostic_severity::error, { source_code_span semicolon; },              \
      MESSAGE(                                                                  \
          QLJS_TRANSLATABLE("for-of loop expression cannot have semicolons"),   \
          semicolon))                                                           \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_unopened_block_comment, "E0210", diagnostic_severity::error,         \
      { source_code_span comment_close; },                                      \
      MESSAGE(QLJS_TRANSLATABLE("unopened block comment"), comment_close))      \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_unused_variable_shadows, "E0196", diagnostic_severity::warning,      \
      {                                                                         \
        identifier shadowing_declaration;                                       \
        identifier shadowed_declaration;                                        \
      },                                                                        \
      MESSAGE(QLJS_TRANSLATABLE("new variable shadows existing variable"),      \
              shadowing_declaration)                                            \
          MESSAGE(QLJS_TRANSLATABLE("existing variable declared here"),         \
                  shadowed_declaration))                                        \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_no_digits_in_binary_number, "E0049", diagnostic_severity::error,     \
      { source_code_span characters; },                                         \
      MESSAGE(QLJS_TRANSLATABLE("binary number literal has no digits"),         \
              characters))                                                      \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_no_digits_in_hex_number, "E0050", diagnostic_severity::error,        \
      { source_code_span characters; },                                         \
      MESSAGE(QLJS_TRANSLATABLE("hex number literal has no digits"),            \
              characters))                                                      \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_no_digits_in_octal_number, "E0051", diagnostic_severity::error,      \
      { source_code_span characters; },                                         \
      MESSAGE(QLJS_TRANSLATABLE("octal number literal has no digits"),          \
              characters))                                                      \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_non_null_assertion_not_allowed_in_parameter, "E0260",                \
      diagnostic_severity::error, { source_code_span bang; },                   \
      MESSAGE(                                                                  \
          QLJS_TRANSLATABLE(                                                    \
              "TypeScript non-null assertion is not allowed on parameters"),    \
          bang))                                                                \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_unexpected_hash_character, "E0052", diagnostic_severity::error,      \
      { source_code_span where; },                                              \
      MESSAGE(QLJS_TRANSLATABLE("unexpected '#'"), where))                      \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_unexpected_bom_before_shebang, "E0095", diagnostic_severity::error,  \
      { source_code_span bom; },                                                \
      MESSAGE(QLJS_TRANSLATABLE(                                                \
                  "unicode byte order mark (BOM) cannot appear before #! "      \
                  "at beginning of script"),                                    \
              bom))                                                             \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_unexpected_identifier_in_expression, "E0147",                        \
      diagnostic_severity::error, { identifier unexpected; },                   \
      MESSAGE(                                                                  \
          QLJS_TRANSLATABLE(                                                    \
              "unexpected identifier in expression; missing operator before"),  \
          unexpected))                                                          \
                                                                                \
  /* NOTE(strager): Try not to use this error. Find or make a more descriptive  \
     and helpful error instead. */                                              \
  QLJS_DIAG_TYPE(                                                               \
      diag_unexpected_token, "E0054", diagnostic_severity::error,               \
      { source_code_span token; },                                              \
      MESSAGE(QLJS_TRANSLATABLE("unexpected token"), token))                    \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_unexpected_token_after_export, "E0112", diagnostic_severity::error,  \
      { source_code_span unexpected_token; },                                   \
      MESSAGE(QLJS_TRANSLATABLE(                                                \
                  "unexpected token in export; expected 'export default ...' "  \
                  "or 'export {{name}' or 'export * from ...' or 'export "      \
                  "class' or 'export function' or 'export let'"),               \
              unexpected_token))                                                \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_unexpected_token_in_variable_declaration, "E0114",                   \
      diagnostic_severity::error, { source_code_span unexpected_token; },       \
      MESSAGE(QLJS_TRANSLATABLE("unexpected token in variable declaration; "    \
                                "expected variable name"),                      \
              unexpected_token))                                                \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_unmatched_indexing_bracket, "E0055", diagnostic_severity::error,     \
      { source_code_span left_square; },                                        \
      MESSAGE(QLJS_TRANSLATABLE("unmatched indexing bracket"), left_square))    \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_unmatched_parenthesis, "E0056", diagnostic_severity::error,          \
      { source_code_span where; },                                              \
      MESSAGE(QLJS_TRANSLATABLE("unmatched parenthesis"), where))               \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_unmatched_right_curly, "E0143", diagnostic_severity::error,          \
      { source_code_span right_curly; },                                        \
      MESSAGE(QLJS_TRANSLATABLE("unmatched '}'"), right_curly))                 \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_use_of_undeclared_parameter_in_type_predicate, "E0315",              \
      diagnostic_severity::error, { identifier name; },                         \
      MESSAGE(QLJS_TRANSLATABLE("{0} is not the name of a parameter"), name))   \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_use_of_undeclared_type, "E0214", diagnostic_severity::warning,       \
      { identifier name; },                                                     \
      MESSAGE(QLJS_TRANSLATABLE("use of undeclared type: {0}"), name))          \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_use_of_undeclared_variable, "E0057", diagnostic_severity::warning,   \
      { identifier name; },                                                     \
      MESSAGE(QLJS_TRANSLATABLE("use of undeclared variable: {0}"), name))      \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_variable_used_before_declaration, "E0058",                           \
      diagnostic_severity::error,                                               \
      {                                                                         \
        identifier use;                                                         \
        identifier declaration;                                                 \
      },                                                                        \
      MESSAGE(QLJS_TRANSLATABLE("variable used before declaration: {0}"), use)  \
          MESSAGE(QLJS_TRANSLATABLE("variable declared here"), declaration))    \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_function_call_before_declaration_in_block_scope, "E0077",            \
      diagnostic_severity::warning,                                             \
      {                                                                         \
        identifier use;                                                         \
        identifier declaration;                                                 \
      },                                                                        \
      MESSAGE(QLJS_TRANSLATABLE(                                                \
                  "function called before declaration in block scope: {0}"),    \
              use)                                                              \
          MESSAGE(QLJS_TRANSLATABLE("function declared here"), declaration))    \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_import_cannot_have_declare_keyword, "E0360",                         \
      diagnostic_severity::error, { source_code_span declare_keyword; },        \
      MESSAGE(QLJS_TRANSLATABLE("cannot use 'declare' keyword with 'import'"),  \
              declare_keyword))                                                 \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_interface_fields_cannot_have_initializers, "E0221",                  \
      diagnostic_severity::error, { source_code_span equal; },                  \
      MESSAGE(QLJS_TRANSLATABLE(                                                \
                  "TypeScript interface fields cannot be initalized"),          \
              equal))                                                           \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_interface_methods_cannot_be_async, "E0217",                          \
      diagnostic_severity::error, { source_code_span async_keyword; },          \
      MESSAGE(QLJS_TRANSLATABLE(                                                \
                  "TypeScript interface methods cannot be marked 'async'"),     \
              async_keyword))                                                   \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_interface_methods_cannot_be_generators, "E0218",                     \
      diagnostic_severity::error, { source_code_span star; },                   \
      MESSAGE(                                                                  \
          QLJS_TRANSLATABLE(                                                    \
              "TypeScript interface methods cannot be marked as a generator"),  \
          star))                                                                \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_interface_methods_cannot_contain_bodies, "E0220",                    \
      diagnostic_severity::error, { source_code_span body_start; },             \
      MESSAGE(QLJS_TRANSLATABLE(                                                \
                  "TypeScript interface methods cannot contain a body"),        \
              body_start))                                                      \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_interface_properties_cannot_be_explicitly_public, "E0237",           \
      diagnostic_severity::error, { source_code_span public_keyword; },         \
      MESSAGE(QLJS_TRANSLATABLE("interface properties "                         \
                                "cannot be marked public explicitly"),          \
              public_keyword))                                                  \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_interface_properties_cannot_be_private, "E0219",                     \
      diagnostic_severity::error,                                               \
      { source_code_span property_name_or_private_keyword; },                   \
      MESSAGE(                                                                  \
          QLJS_TRANSLATABLE(                                                    \
              "interface properties are always public and cannot be private"),  \
          property_name_or_private_keyword))                                    \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_interface_properties_cannot_be_protected, "E0288",                   \
      diagnostic_severity::error, { source_code_span protected_keyword; },      \
      MESSAGE(QLJS_TRANSLATABLE("TypeScript interface properties are always "   \
                                "public and cannot be marked protected"),       \
              protected_keyword))                                               \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_interface_properties_cannot_be_static, "E0216",                      \
      diagnostic_severity::error, { source_code_span static_keyword; },         \
      MESSAGE(QLJS_TRANSLATABLE(                                                \
                  "TypeScript interface properties cannot be 'static'"),        \
              static_keyword))                                                  \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_invalid_break, "E0200", diagnostic_severity::error,                  \
      { source_code_span break_statement; },                                    \
      MESSAGE(QLJS_TRANSLATABLE(                                                \
                  "break can only be used inside of a loop or switch"),         \
              break_statement))                                                 \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_invalid_continue, "E0201", diagnostic_severity::error,               \
      { source_code_span continue_statement; },                                 \
      MESSAGE(QLJS_TRANSLATABLE("continue can only be used inside of a loop"),  \
              continue_statement))                                              \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_pointless_string_comp_contains_lower, "E0286",                       \
      diagnostic_severity::warning, { source_code_span span_operator; },        \
      MESSAGE(                                                                  \
          QLJS_TRANSLATABLE("lower case letters compared with toUpperCase"),    \
          span_operator))                                                       \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_pointless_string_comp_contains_upper, "E0287",                       \
      diagnostic_severity::warning, { source_code_span span_operator; },        \
      MESSAGE(                                                                  \
          QLJS_TRANSLATABLE("upper case letters compared with toLowerCase"),    \
          span_operator))                                                       \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_pointless_strict_comp_against_array_literal, "E0341",                \
      diagnostic_severity::warning, { source_code_span equals_operator; },      \
      MESSAGE(                                                                  \
          QLJS_TRANSLATABLE(                                                    \
              "using '{0}' against an array literal does not compare items"),   \
          equals_operator))                                                     \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_pointless_comp_against_arrow_function, "E0342",                      \
      diagnostic_severity::warning,                                             \
      {                                                                         \
        source_code_span equals_operator;                                       \
        string8_view comparison_result;                                         \
      },                                                                        \
      MESSAGE(QLJS_TRANSLATABLE("using '{0}' against an arrow "                 \
                                "function always returns '{1}'"),               \
              equals_operator, comparison_result))                              \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_pointless_comp_against_class_literal, "E0343",                       \
      diagnostic_severity::warning,                                             \
      {                                                                         \
        source_code_span equals_operator;                                       \
        string8_view comparison_result;                                         \
      },                                                                        \
      MESSAGE(QLJS_TRANSLATABLE("using '{0}' against a class "                  \
                                "literal always returns '{1}'"),                \
              equals_operator, comparison_result))                              \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_pointless_strict_comp_against_empty_array_literal, "E0344",          \
      diagnostic_severity::warning,                                             \
      {                                                                         \
        source_code_span equals_operator;                                       \
        string8_view comparison_result;                                         \
      },                                                                        \
      MESSAGE(QLJS_TRANSLATABLE("'{0} []' is always '{1}'"), equals_operator,   \
              comparison_result))                                               \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_pointless_comp_against_object_literal, "E0345",                      \
      diagnostic_severity::warning,                                             \
      {                                                                         \
        source_code_span equals_operator;                                       \
        string8_view comparison_result;                                         \
      },                                                                        \
      MESSAGE(QLJS_TRANSLATABLE("using '{0}' against an object "                \
                                "literal always returns '{1}'"),                \
              equals_operator, comparison_result))                              \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_pointless_comp_against_regular_expression_literal, "E0346",          \
      diagnostic_severity::warning,                                             \
      {                                                                         \
        source_code_span equals_operator;                                       \
        string8_view comparison_result;                                         \
      },                                                                        \
      MESSAGE(QLJS_TRANSLATABLE("using '{0}' against a regular "                \
                                "expression literal always returns '{1}'"),     \
              equals_operator, comparison_result))                              \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_unexpected_function_parameter_is_parenthesized, "E0349",             \
      diagnostic_severity::error,                                               \
      { source_code_span left_paren_to_right_paren; },                          \
      MESSAGE(QLJS_TRANSLATABLE("function parameter cannot be parenthesized"),  \
              left_paren_to_right_paren))                                       \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_unexpected_comma_after_field_initialization, "E0330",                \
      diagnostic_severity::error, { source_code_span comma; },                  \
      MESSAGE(QLJS_TRANSLATABLE("',' should be ';' instead"), comma))           \
                                                                                \
  QLJS_DIAG_TYPE(                                                               \
      diag_unexpected_colon_after_generic_definition, "E0331",                  \
      diagnostic_severity::error, { source_code_span colon; },                  \
      MESSAGE(QLJS_TRANSLATABLE("':' should be 'extends' instead"), colon))     \
  /* END */

// QLJS_X_RESERVED_DIAG_TYPES lists reserved error codes. These codes were used
// in the past but no longer mean anything.
//
// When removing a diagnostic from QLJS_X_DIAG_TYPES, add an entry to
// QLJS_X_RESERVED_DIAG_TYPES.
//
// QLJS_DIAG_TYPE should have the following signature:
//
// #define QLJS_DIAG_TYPE(error_name, error_code, severity, struct_body,
// format) ...
//
// * error_name: (unset)
// * error_code: string literal
// * severity: (unset)
// * struct_body: (unset)
// * format: (unset)
#define QLJS_X_RESERVED_DIAG_TYPES \
  QLJS_DIAG_TYPE(, "E0242", , , )  \
  QLJS_DIAG_TYPE(, "E0271", , , )  \
  QLJS_DIAG_TYPE(, "E0279", , , )  \
  QLJS_DIAG_TYPE(, "E0707", , , )  \
  /* END */

namespace quick_lint_js {
#define QLJS_DIAG_TYPE(name, code, severity, struct_body, format_call) \
  struct name struct_body;
QLJS_X_DIAG_TYPES
#undef QLJS_DIAG_TYPE

enum class diag_type {
#define QLJS_DIAG_TYPE(name, code, severity, struct_body, format_call) name,
  QLJS_X_DIAG_TYPES
#undef QLJS_DIAG_TYPE
};

std::ostream& operator<<(std::ostream&, diag_type);

template <class Error>
struct diag_type_from_type_detail;

#define QLJS_DIAG_TYPE(name, code, severity, struct_body, format_call) \
  template <>                                                          \
  struct diag_type_from_type_detail<name> {                            \
    static constexpr diag_type type = diag_type::name;                 \
  };
QLJS_X_DIAG_TYPES
#undef QLJS_DIAG_TYPE

template <class Error>
inline constexpr diag_type diag_type_from_type =
    diag_type_from_type_detail<Error>::type;

inline constexpr int diag_type_count = 0
#define QLJS_DIAG_TYPE(name, code, severity, struct_body, format_call) +1
    QLJS_X_DIAG_TYPES
#undef QLJS_DIAG_TYPE
    ;
}

#endif

// quick-lint-js finds bugs in JavaScript programs.
// Copyright (C) 2020  Matthew "strager" Glazar
//
// This file is part of quick-lint-js.
//
// quick-lint-js is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// quick-lint-js is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with quick-lint-js.  If not, see <https://www.gnu.org/licenses/>.
