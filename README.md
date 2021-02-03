# adaptr

<!-- badges: start -->
[![CRAN Status](https://www.r-pkg.org/badges/version/adaptr)](https://cran.r-project.org/package=adaptr)
[![Package Lifecycle](https://img.shields.io/badge/lifecycle-experimental-orange.svg)](https://www.tidyverse.org/lifecycle/#experimental)
[![License: MIT](https://img.shields.io/github/license/PRL-PRG/adaptr)](https://opensource.org/licenses/MIT)
[![Build Status](https://github.com/PRL-PRG/adaptr/workflows/R-CMD-check/badge.svg)](https://github.com/PRL-PRG/adaptr/actions?query=workflow%3AR-CMD-check)
[![lintr Status](https://github.com/PRL-PRG/adaptr/workflows/lintr/badge.svg)](https://github.com/PRL-PRG/adaptr/actions?query=workflow%3Alintr)
[![clang-tidy](https://github.com/PRL-PRG/adaptr/workflows/clang-tidy/badge.svg)](https://github.com/PRL-PRG/adaptr/actions?query=workflow%3Aclang-tidy)
[![cppcheck Status](https://github.com/PRL-PRG/adaptr/workflows/cppcheck/badge.svg)](https://github.com/PRL-PRG/adaptr/actions?query=workflow%3Acppcheck)
[![rchk](https://github.com/PRL-PRG/adaptr/workflows/rchk/badge.svg)](https://github.com/PRL-PRG/adaptr/actions?query=workflow%3Archk)
[![Code Coverage](https://codecov.io/gh/PRL-PRG/adaptr/branch/master/graph/badge.svg)](https://codecov.io/gh/PRL-PRG/adaptr)
<!-- badges: end -->


## Overview

[adaptr](https://prl-prg.github.io/adaptr/) is an interop library that exposes
a native object type that can be used both in R and native code. 
The exposed object type has a unique id, is reference counted and allows attaching arbitrary R value.

## Setup

To install the latest version, run the following R command:

```r
devtools::install_github("PRL-PRG/adaptr")
```

To uninstall the existing version, run the following R command:

```r
remove.packages("adaptr")
```


## Getting help

Please report bugs with a minimal reproducible example at [GitHub](https://github.com/PRL-PRG/adaptr/issues).

Request new features with use cases at [GitHub](https://github.com/PRL-PRG/adaptr/issues).

